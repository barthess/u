#include <math.h>
#include <string.h>
#include <limits.h>

#include "main.h"
#include "global_flags.h"
#include "message.hpp"
#include "mavdbg.hpp"
#include "param_registry.hpp"
#include "misc_math.hpp"
#include "eeprom_file.hpp"
#include "eeprom_file_tree.hpp"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */
#define ADDITIONAL_WRITE_TMO    MS2ST(10)

#define PARAM_CONFIRM_TMO       MS2ST(1000)
#define PARAM_POST_TMO          MS2ST(50)

#define SEND_VALUE_PAUSE        MS2ST(50)

#define PARAM_VALUE_SIZE        (sizeof(*((GlobalParam[0]).valuep)))
#define PARAM_RECORD_SIZE       (PARAM_ID_SIZE + PARAM_VALUE_SIZE)

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */
static void acquire(void);
static void release(void);

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */
ParamRegistry param_registry;
extern GlobalFlags_t GlobalFlags;
extern EepromFile ParamFile;

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

#include "param_autogenerated.cpp"

const GlobalParam_t *ParamRegistry::param_array = GlobalParam;
static uint8_t eeprombuf[PARAM_RECORD_SIZE];
static chibios_rt::BinarySemaphore sem(false);

/*
 *******************************************************************************
 *******************************************************************************
 * LOCAL FUNCTIONS
 *******************************************************************************
 *******************************************************************************
 */
/**
 *
 */
static void acquire(void){
  sem.wait();
}

/**
 *
 */
static void release(void){
  sem.signal();
}

/**
 * @brief   Performs key-value search. Low level function
 *
 * @return      Index in dictionary.
 * @retval -1   key not found.
 */
int32_t ParamRegistry::key_index_search(const char* key){
  int32_t i = 0;

  for (i = 0; i < OnboardParamCount; i++){
    if (strcmp(key, GlobalParam[i].name) == 0)
      return i;
  }
  return -1;
}

/**
 * Return pointer to value. Hi level function.
 */
void *ParamRegistry::valueSearch(const char *key){
  int32_t i = -1;

  chDbgCheck(GlobalFlags.parameters_loaded == 1, "parameters not ready");

  i = this->key_index_search(key);
  if (i == -1){
    chDbgPanic("key not found");
    return NULL;
  }
  else
    return GlobalParam[i].valuep;
}

/**
 *
 */
ParamRegistry::ParamRegistry(void){
  int32_t i = 0;
  int32_t n = 0;
  int32_t len = 0;

  len = paramCount();

  chDbgCheck((sizeof(gp_val) / sizeof(gp_val[0])) == len,
      "sizes of volatile array and param array must be equal");
  val = gp_val;

  /* initialise variable array with zeroes to be safer */
  floatint v;
  v.u32 = 0;
  for (i = 0; i < len; i++){
    val[i] = v;
  }

  /* check hardcoded name lengths */
  for (i = 0; i<len; i++){
    if (sizeof (*(param_array[i].name)) > ONBOARD_PARAM_NAME_LENGTH)
      chDbgPanic("name too long");
  }

  /* check for keys' names collisions */
  for (n=0; n<len; n++){
    for (i=n+1; i<len; i++){
      if (0 == strcmp(param_array[i].name, param_array[n].name))
        chDbgPanic("name collision detected");
    }
  }

  /* check reserved space in EEPROM */
  chDbgCheck(((PARAM_RECORD_SIZE * this->paramCount()) < EEPROM_SETTINGS_SIZE),
          "not enough space in file");
}

/**
 *
 */
param_status_t ParamRegistry::setParam(void *value, const GlobalParam_t *param){
  return validator.set(value, param);
}

/**
 *
 */
int32_t ParamRegistry::paramCount(void){
  return sizeof(GlobalParam)/sizeof(GlobalParam[0]);
}

/**
 * @brief   Sends mails to communication thread
 *
 * @param[in] key     if NULL than perform search by index
 * @param[in] n       search index
 * @param[out] *i     store founded index
 *
 * @return    pointer to parameter structure
 * @retval    NULL - parameter not found
 */
const GlobalParam_t *ParamRegistry::getParam(const char *key, int32_t n, int32_t *i){
  int32_t index = -1;

  if (key != NULL){
    index = param_registry.key_index_search(key);
    if (-1 == index)
      return NULL;
  }
  else{
    if ((n > paramCount()) || (-1 == n))
      return NULL;
    else
      index = n;
  }

  /**/
  if (NULL != i)
    *i = index;
  return &(param_array[index]);
}

/**
 * This functions created for smooth update of parameter registry in case
 * adding of some new parameters somewhere in middle.
 * 1) get name from MCU's flash
 * 2) perform brute force search in EEPROM file
 */
bool ParamRegistry::load_extensive(void){
  int32_t  i = 0, n = 0;
  uint32_t status = 0;
  uint32_t v = 0;
  bool found = false;

  chDbgCheck(GlobalFlags.i2c_ready == 1, "bus not ready");

  acquire();

  for (i = 0; i < this->paramCount(); i++){
    ParamFile.setPosition(0);
    found = false;

    for (n=0; n<this->paramCount(); n++){
      status = ParamFile.read(eeprombuf, PARAM_RECORD_SIZE);
      if (status < PARAM_RECORD_SIZE){
        chDbgPanic("");
        return PARAM_FAILED;
      }
      if (strcmp((const char *)eeprombuf, GlobalParam[i].name) == 0){
        found = true;
        break;
      }
    }

    /* was parameter previously stored in eeprom */
    if (found){
      v = pack8to32(&(eeprombuf[PARAM_ID_SIZE]));
    }
    else{
      /* use hardcoded default */
      v = GlobalParam[i].def.u32;
    }
    /* check value acceptability and set it */
    validator.set(&v, &(GlobalParam[i]));
  }

  release();
  saveAll();
  return PARAM_SUCCESS;
}

/**
 *
 */
bool ParamRegistry::load(void){
  int32_t  i = 0;
  int32_t  cmpresult = -1;
  uint32_t status = 0;
  uint32_t v = 0;

  chDbgCheck(GlobalFlags.i2c_ready == 1, "bus not ready");

  acquire();
  ParamFile.setPosition(0);

  for (i = 0; i < this->paramCount(); i++){

    /* read field from EEPROM and check number of red bytes */
    status = ParamFile.read(eeprombuf, PARAM_RECORD_SIZE);
    if (status < PARAM_RECORD_SIZE){
      chDbgPanic("");
      return PARAM_FAILED;
    }

    /* if no updates was previously in paramter structure than order of
     * parameters in registry must be the same as in eeprom */
    cmpresult = strcmp(GlobalParam[i].name, (char *)eeprombuf);
    if (0 == cmpresult){   /* OK, this parameter already presents in EEPROM */
      v = pack8to32(&(eeprombuf[PARAM_ID_SIZE]));
    }
    else{
      /* there is not such parameter in EEPROM. Possible reasons:
       * 1) parameter "registry" has been changed.
       * 2) this is very first run of device with totally empty EEPROM
       * To correctly fix this situation we just need to
       * save structure to EEPROM after loading of all parameters to RAM.
       */
      release();
      return load_extensive();
    }

    /* check value acceptability and set it */
    validator.set(&v, &(GlobalParam[i]));
  }

  release();
  return PARAM_SUCCESS;
}

/**
 *
 */
bool ParamRegistry::saveAll(void){
  int32_t  i;
  uint32_t status = 0;
  uint32_t v = 0;
  uint8_t tmpbuf[PARAM_RECORD_SIZE];

  chDbgCheck(GlobalFlags.i2c_ready == 1, "bus not ready");

  acquire();
  ParamFile.setPosition(0);

  for (i = 0; i < this->paramCount(); i++){

    /* first copy parameter name in buffer */
    memcpy(eeprombuf, GlobalParam[i].name, PARAM_ID_SIZE);

    /* now write data */
    v = GlobalParam[i].valuep->u32;
    unpack32to8(v, &(eeprombuf[PARAM_ID_SIZE]));
    status = ParamFile.write(eeprombuf, PARAM_RECORD_SIZE);
    chDbgCheck(status == PARAM_RECORD_SIZE, "write failed");

    /* check written data */
    ParamFile.setPosition(ParamFile.getPosition() - PARAM_RECORD_SIZE);
    status = ParamFile.read(tmpbuf, sizeof(tmpbuf));
    if (0 != memcmp(tmpbuf, eeprombuf, (PARAM_ID_SIZE + sizeof(v))))
      chDbgPanic("Verification failed");

    chThdSleep(ADDITIONAL_WRITE_TMO);
  }

  release();
  return PARAM_SUCCESS;
}

/**
 *
 */
bool ParamRegistry::syncParam(const char* key){
  int32_t  i;
  uint32_t status = 0;
  uint32_t v = 0;
  uint8_t  tmpbuf[PARAM_RECORD_SIZE];

  chDbgCheck(GlobalFlags.i2c_ready == 1, "bus not ready");

  i = key_index_search(key);
  chDbgCheck(i != -1, "Not found");

  acquire();
  ParamFile.setPosition(i * PARAM_RECORD_SIZE);

  /* ensure we found exacly what needed */
  status = ParamFile.read(tmpbuf, sizeof(tmpbuf));
  chDbgCheck(status == sizeof(tmpbuf), "read failed");
  chDbgCheck(strcmp((char *)tmpbuf, key) == 0, "param not found in EEPROM");

  /* write only if value differ */
  ParamFile.setPosition(ParamFile.getPosition() - PARAM_VALUE_SIZE);
  v = ParamFile.readWord();
  if (v != GlobalParam[i].valuep->u32){
    ParamFile.setPosition(ParamFile.getPosition() - PARAM_VALUE_SIZE);
    status = ParamFile.writeWord(GlobalParam[i].valuep->u32);
    chDbgCheck(status == sizeof(uint32_t), "read failed");
    chThdSleep(ADDITIONAL_WRITE_TMO);
  }

  release();
  return PARAM_SUCCESS;
}

/*
 *******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************
 */


