#!/bin/sh
cd build
cat ch.map | grep ".stacks         0x20000000"
STACKS=`cat ch.map | grep ".stacks         0x20000000" | gawk '{print$3}'`

cat ch.map | grep "__ram_start__ ="
RAM_START=`cat ch.map | grep "__ram_start__ =" | gawk '{print$1}'`

cat ch.map | grep "__ram_size__ ="
RAM_MCU=`cat ch.map | grep "__ram_size__ =" | gawk '{print$1}'`

cat ch.map | grep ".data" | grep "load address"
cat ch.map | grep ".bss" | grep "load address"

cat ch.map | grep "_end = ."
PROGRAM=`cat ch.map | grep "_end = ." | gawk '{print$1}'`

cat ch.map | grep "__heap_end__ = (__ram_end__ - __stacks_total_size__)"

FLASH_USED=`du -b ch.bin | gawk '{print$1}'`
FLASH_MCU=1048576
echo "------------------------------------------------------------------------------------------------------------"

let "STACK = STACKS"
let "RAM_MCU = RAM_MCU"
let "RAM_USED = PROGRAM - RAM_START"
let "PROGRAM = PROGRAM - RAM_START - STACK"
let "FLASH_PERCENT = (100 * FLASH_USED)/FLASH_MCU"
let "RAM_PERCENT = (100 * RAM_USED)/RAM_MCU"

echo "SRAM:  stacks = $STACK, program = $PROGRAM, total = $RAM_USED, mcu_ram = $RAM_MCU, utilization = $RAM_PERCENT%"
echo "FLASH: program = $FLASH_USED, mcu_flash = $FLASH_MCU, utilization = $FLASH_PERCENT%"
