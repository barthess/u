#!/bin/sh
FLASH_SIZE=1048576
FLASH_USED=`du -b build/ch.bin | gawk '{print$1}'`

RAM_SIZE=`cat build/ch.map | grep "__ram_size__ =" | gawk '{print$1}'`
RAM_USED=`arm-none-eabi-size build/ch.elf | tail -1 | awk '{print $2+$3}'`

echo "------------------------------------------------------------------------------------------------------------"

let "FLASH_PERCENT	= (100 * FLASH_USED)/FLASH_SIZE"
let "RAM_SIZE		= RAM_SIZE" # to convert from hex to dec
let "RAM_PERCENT	= (100 * RAM_USED)/RAM_SIZE"

echo "SRAM:  used = $RAM_USED, mcu_ram = $RAM_SIZE, utilization = $RAM_PERCENT%"
echo "FLASH: program = $FLASH_USED, mcu_flash = $FLASH_SIZE, utilization = $FLASH_PERCENT%"
