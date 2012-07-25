#ifndef MAVSENDER2_H_
#define MAVSENDER2_H_



typedef struct tlm_registry_t tlm_registry_t;

/* sendinf function */
typedef bool_t (*send_t)(void);

struct tlm_registry_t
{
  /* how much to sleep */
  uint16_t next_dealine;
  /* pointer to period value in global parameters structure */
  uint32_t *sleepperiod; /* handle here negative values in case of changes from ground */
  /* sending function */
  const send_t sender;
};

void TlmSenderInit(void);

#endif /* MAVSENDER2_H_ */
