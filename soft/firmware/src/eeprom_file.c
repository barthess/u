#include "ch.h"
#include "hal.h"

#include "eeprom.h"



static size_t write(void *ip, const uint8_t *bp, size_t n){
  return 0;
}


static size_t read(void *ip, uint8_t *bp, size_t n){
  uint32_t pos = &((BaseFileStream *)ip)->vmt;
  eeprom_read(pos, (uint16_t)(n & 0xFFFF), bp);


  return 0;
}





static uint32_t close(void *ip) {
  (void)ip;
  return 0;
}
static int geterror(void *ip){
  return 0;
}
static fileoffset_t getsize(void *ip){
  (void)ip;
  return EEPROM_SIZE;
}
static fileoffset_t getposition(void *ip){
  return 0;
}
static fileoffset_t lseek(void *ip, fileoffset_t offset){
  return 0;
}

static const struct BaseFilelStreamVMT vmt = {
    write,
    read,
    close,
    geterror,
    getsize,
    getposition,
    lseek
};

static const BaseFileStream bfs = {&vmt};


void EeepromOpen(void){
  (void)bfs;
//  bfs.vmt = &vmt;
}



