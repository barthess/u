#!/bin/bash

openocd -c "gdb_memory_map enable" \
	-c "gdb_flash_program enable" \
	-c "reset_config trst_and_srst" \
	-c "log_output openocd.log" \
	-f /usr/share/openocd/scripts/interface/olimex-arm-usb-ocd.cfg \
	-f /usr/share/openocd/scripts/target/stm32f4x.cfg
