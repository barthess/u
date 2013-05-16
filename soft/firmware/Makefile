##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
__OPT = -ggdb -fomit-frame-pointer -falign-functions=16 -fno-strict-aliasing
ifeq ($(USE_OPT),)
  USE_OPT     = -O2 $(__OPT)
  USE_OPT_DBG = -O0 $(__OPT)
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT     = -std=gnu99
  USE_COPT_DBG = $(USE_COPT)
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT     = -fno-rtti -fno-exceptions
  USE_CPPOPT_DBG = $(USE_CPPOPT)
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Enables the use of FPU on Cortex-M4.
ifeq ($(USE_FPU),)
  USE_FPU = yes
endif

# Enable this if you really want to use the STM FWLib.
ifeq ($(USE_FWLIB),)
  USE_FWLIB = no
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Define project name here
PROJECT = ch

# Imported source files
CHIBIOS = ../../../chibios-svn
include $(CHIBIOS)/boards/NONSTANDARD_STM32F4_BARTHESS1/board.mk
include $(CHIBIOS)/os/hal/platforms/STM32F4xx/platform.mk
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/ports/GCC/ARMCMx/STM32F4xx/port.mk
include $(CHIBIOS)/os/kernel/kernel.mk
include $(CHIBIOS)/os/various/fatfs_bindings/fatfs.mk
include $(CHIBIOS)/os/various/cpp_wrappers/kernel.mk
#include $(CHIBIOS)/test/test.mk

# Define linker script file here
LDSCRIPT= STM32F407xG_flash_end.ld
#LDSCRIPT= $(PORTLD)/STM32F407xG.ld

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = $(PORTSRC) \
       $(KERNSRC) \
       $(TESTSRC) \
       $(HALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
       $(CHIBIOS)/os/various/evtimer.c \
       $(CHIBIOS)/os/various/syscalls.c \
       $(FATFSSRC) \
       $(CHIBIOS)/os/various/chprintf.c \
       $(CHIBIOS)/os/various/chrtclib.c \
       $(CHIBIOS)/os/various/shell.c \
       src/microrl/src/microrl.c\
       
CSRC_DBG = src/fault_handlers.c \


# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
MATHSRC = src/math/misc_math.cpp \
         src/math/sphere.cpp \
     	 src/math/geometry.cpp \
     	 src/math/dsp.cpp \
     
SENSORSSRC = src/sensors/sensors.cpp \
         src/sensors/adc_local.cpp \
         src/sensors/exti_local.cpp \
         src/sensors/gps.cpp \
         src/sensors/sensors_cli.cpp \
         src/sensors/tmp75.cpp \
         src/sensors/itg3200.cpp \
         src/sensors/itg3200_cal.cpp \
         src/sensors/lsm303.cpp \
         src/sensors/lsm303_cal.cpp \
         src/sensors/mma8451.cpp \
         src/sensors/bmp085.cpp \
         src/sensors/max1236.cpp \
         src/sensors/speedometer.cpp \
         src/sensors/imu.cpp \
		 src/sensors/sins.cpp \
		 
MAVLINKSRC = src/mavlink_local/param.cpp \
         src/mavlink_local/param_registry.cpp \
         src/mavlink_local/param_validator.cpp \
         src/mavlink_local/mavdbg.cpp \
         src/mavlink_local/param_cli.cpp \
         src/mavlink_local/wps_cli.cpp \
         src/mavlink_local/waypoint_db.cpp \
         
KINEMATICSRC = src/kinematic/dcm.cpp \
         src/kinematic/dcm_cli.cpp \
         src/kinematic/airspeed.cpp \
         src/kinematic/madgwick.cpp

ACSSRC = src/acs/controller.cpp \
         src/acs/mission_updater.cpp \
		 src/acs/acs.cpp \
		 src/acs/acs_rover.cpp \
		 src/acs/acs_rover_loiter.cpp \
		 src/acs/acs_rover_takeoff.cpp \
		 src/acs/acs_rover_navigate.cpp \
		 src/acs/acs_rover_passwp.cpp \
		 src/acs/acs_rover_land.cpp \
		 src/acs/acs_rover_pause.cpp \
		 src/acs/acs_rover_idle.cpp \
		 src/acs/mission_planner.cpp \
		          
LINKSRC = src/datalink/linkmgr.cpp \
         src/datalink/link.cpp \
         src/datalink/link_packer.cpp \
         src/datalink/link_unpacker.cpp \
         src/datalink/tlm_sender.cpp \
         src/datalink/usbcfg.cpp

CPPSRC = $(CHCPPSRC) \
		 $(MAVLINKSRC) \
		 $(KINEMATICSRC) \
	 	 $(LINKSRC) \
 		 $(MATHSRC) \
 		 $(SENSORSSRC) \
		 main.cpp \
		 src/gcc_stubs.cpp \
         src/message.cpp \
         src/sanity.cpp \
         src/blinker.cpp \
         src/timekeeping.cpp \
         src/pwr_mgmt.cpp \
		 src/eeprom/cpp/eeprom_file.cpp \
         src/eeprom/cpp/eeprom_fs.cpp \
         src/eeprom/cpp/eeprom_mtd.cpp \
         src/eeprom/cpp/eeprom_testsuit.cpp \
         src/i2c_local.cpp \
         src/utils/memfunc.cpp \
         src/storage/microsd.cpp \
         src/storage/logger.cpp \
         src/storage/logger_mavencoder.cpp \
         src/storage/eeprom_file_tree.cpp \
         src/cli/cli.cpp \
         src/cli/cli_cmd.cpp \
         src/drivetrain/servo.cpp \
         src/drivetrain/drivetrain.cpp \
         src/drivetrain/servo_cli.cpp \
         src/irq_storm.cpp \
         src/calibration/cli_cal.cpp \
         src/benchmark/benchmark.cpp

CPPSRC_DBG = $(ACSSRC) \


# C sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACSRC =

# C++ sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACPPSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCPPSRC =

# List ASM source files here
ASMSRC = $(PORTASM)

# Dir with mavlink headers
MAVLINKDIR = ../mavlink/C

INCDIR = $(PORTINC) $(KERNINC) $(TESTINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) \
         $(CHIBIOS)/os/various \
         $(CHIBIOS)/os/fs \
		 $(FATFSINC) \
         $(CHCPPINC) \
         src \
         src/eeprom/cpp \
         src/datalink \
         src/cli \
         src/sensors \
         src/storage \
         src/kinematic \
         src/acs \
         src/mavlink_local \
         src/drivetrain \
         src/math \
         src/calibration \
         src/utils \
         src/benchmark \
         $(MAVLINKDIR)/common \
         
#
# Project, sources and paths
##############################################################################

##############################################################################
# Compiler settings
#

# -lm - это указание линкеру для подключения математической либы.
# добавлено именно здесь, потому что больше некуда
MCU  = cortex-m4
#MCU  = cortex-m3 -lm

TRGT = arm-none-eabi-

ifeq ($(shell uname -o),GNU/Linux)
	CC   = ccache $(TRGT)gcc
	CPPC = ccache $(TRGT)g++
else
	CC   = $(TRGT)gcc
	CPPC = $(TRGT)g++	
endif

# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
LD   = $(TRGT)gcc
#LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
OD   = $(TRGT)objdump
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT = 

# THUMB-specific options here
TOPT = -mthumb -DTHUMB

# Define common warning options here
WARN = -Wall -Wextra -Wdouble-promotion -Wformat #-Wconversion -Werror

# Define C warning options here
CWARN = $(WARN) -Wstrict-prototypes

# Define C++ warning options here
CPPWARN = $(WARN) -Woverloaded-virtual -Wctor-dtor-privacy  -Winit-self -Wunreachable-code #-Wconversion -Wsign-conversion #-Wold-style-cast #-Wnon-virtual-dtor #-Weffc++

#
# Compiler settings
##############################################################################

##############################################################################
# Start of default section
#

# List all default C defines here, like -D_DEBUG=1
DDEFS =

# List all default ASM defines here, like -D_DEBUG=1
DADEFS =

# List all default directories to look for include files here
DINCDIR =

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS = -lm

#
# End of default section
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS =

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR =

# List the user directory to look for the libraries here
ULIBDIR = 

# List all user libraries here
ULIBS =

#
# End of user defines
##############################################################################

ifeq ($(USE_FPU),yes)
  FPU_OPT = -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -fsingle-precision-constant
  #FPU_OPT = -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant
  USE_OPT     += $(FPU_OPT)
  USE_OPT_DBG += $(FPU_OPT)
  DDEFS += -DCORTEX_USE_FPU=TRUE
else
  DDEFS += -DCORTEX_USE_FPU=FALSE
endif

ifeq ($(USE_FWLIB),yes)
  include $(CHIBIOS)/ext/stm32lib/stm32lib.mk
  CSRC += $(STM32SRC)
  INCDIR += $(STM32INC)
  USE_OPT += -DUSE_STDPERIPH_DRIVER
endif

include $(CHIBIOS)/os/ports/GCC/ARMCMx/rules.mk


######## resource usage show ################
MAKE_ALL_RULE_HOOK: res_usage

res_usage: $(BUILDDIR)/$(PROJECT).bin $(BUILDDIR)/$(PROJECT).elf \
			$(BUILDDIR)/$(PROJECT).hex $(BUILDDIR)/$(PROJECT).dmp
	./res_usage.sh	
	
######### autogeneration rules ##############
src/mavlink_local/param.cpp: src/mavlink_local/param_autogenerated.cpp
src/mavlink_local/param_autogenerated.cpp: gen_param_struct.py
	 rm -f $@
	 python $< -n ns > $@

src/link/link_packer.cpp: gen_link_packer.py
	python $<

src/link/link_unpacker.cpp: gen_link_unpacker.py
	python $<

src/link/tlm_sender.cpp: gen_tlm_sender.py
	python $<
	
src/storage/logger_mavencoder.cpp: gen_logger_mavencoder.py
	python $<

src/sensors/bmp085.cpp: src/sensors/bmp085_tab_autogenerated.h 
src/sensors/bmp085_tab_autogenerated.h: src/sensors/gen_bmp085_table.py
	rm -f $@
	python $< > $@

clean: autogen_clean
autogen_clean:
	rm -f src/mavlink_local/param_autogenerated.cpp \
		  src/sensors/bmp085_tab_autogenerated.h \
		  src/link/link_packer.cpp \
		  src/link/link_unpacker.cpp \
		  src/link/tlm_sender.cpp \
		  src/storage/logger_mavencoder.cpp \
