##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
ifeq ($(USE_OPT),)
  #USE_OPT = -O2 -ggdb -fno-strict-aliasing -fomit-frame-pointer -falign-functions=16 -mhard-float -mfpu=fpv4-sp-d16 -fsingle-precision-constant
  USE_OPT = -O0 -ggdb -fomit-frame-pointer -falign-functions=16 -fno-strict-aliasing -std=gnu99
  #USE_OPT = -O0 -ggdb -fomit-frame-pointer -std=gnu99
  #USE_OPT = -O2 -ggdb -fomit-frame-pointer -falign-functions=16 -fno-strict-aliasing
  #USE_OPT = -O3 -ggdb -fomit-frame-pointer -falign-functions=16
  #USE_OPT = -Os -ggdb -fomit-frame-pointer -falign-functions=16
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable register caching optimization (read documentation).
ifeq ($(USE_CURRP_CACHING),)
  USE_CURRP_CACHING = no
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
CHIBIOS = ../../../chibios
include $(CHIBIOS)/boards/NONSTANDARD_STM32F4_BARTHESS1/board.mk
include $(CHIBIOS)/os/hal/platforms/STM32F4xx/platform.mk
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/ports/GCC/ARMCMx/STM32F4xx/port.mk
include $(CHIBIOS)/os/kernel/kernel.mk
include $(CHIBIOS)/os/various/fatfs_bindings/fatfs.mk
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
       $(CHIBIOS)/os/various/memstreams.c \
       main.c \
       src/stubs.c \
       src/utils.c \
       src/bkp.c \
       src/i2c_local.c \
       src/exti_local.c \
       src/microrl/src/microrl.c \
       src/sensors/gps.c \
       src/irq_storm.c \
       src/storage/microsd.c \
       src/storage/logger.c \
       src/servo.c \
       src/kinematic/imu.c \
       src/kinematic/vector3d.c \
       src/kinematic/dcm.c \
       src/kinematic/airspeed.c \
       src/sanity.c \
       src/parameters/param.c \
       src/parameters/persistant.c \
       src/timekeeping.c \
       src/sensors/adc_local.c \
       src/sensors/sensors.c \
       src/sensors/max1236.c \
       src/sensors/tmp75.c \
       src/sensors/bmp085.c \
       src/sensors/mma8451.c \
       src/sensors/mag3110.c \
       src/sensors/itg3200.c \
       src/sensors/mavsender.c \
       src/cli/cli.c \
       src/cli/cli_cmd.c \
       src/link/linkmgr.c \
       src/link/link.c \
       src/link/link_sortout.c \
       src/link/link_sortin.c \
       src/eeprom/24aa.c \
       src/eeprom/eeprom.c \
       src/eeprom/eeprom_testsuit.c \
       src/autopilot.c \
       src/message.c \
       #src/bkp.c
       
       

DSPSRC = cortex_dsp
CSRC += $(DSPSRC)/arm_common_tables.c \
		$(DSPSRC)/arm_sqrt_q31.c \
        $(DSPSRC)/arm_sqrt_q15.c \
        $(DSPSRC)/arm_cos_f32.c \
        $(DSPSRC)/arm_cos_q31.c \
        $(DSPSRC)/FilteringFunctions/arm_fir_q31.c \
        $(DSPSRC)/FilteringFunctions/arm_fir_fast_q31.c \
        
        

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC =

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
         $(CHIBIOS)/os/various  $(FATFSINC) \
         include \
         src/eeprom \
         src/link \
         src/cli \
         src/sensors \
         src/storage \
         src/kinematic \
         src/parameters \
         $(MAVLINKDIR) \
         $(MAVLINKDIR)/common \
         $(MAVLINKDIR)/bart
         
#
# Project, sources and paths
##############################################################################

##############################################################################
# Compiler settings
#

# -lm - это указание линкеру для подключения математической либы.
# добавлено именно здесь, потому что больше некуда
MCU  = cortex-m4 -lm
#MCU  = cortex-m3 -lm

#TRGT = arm-elf-
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.

LD   = $(CC)
#LD   = $(CPPC)
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
OD   = $(TRGT)objdump
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# ARM-specific options here
AOPT = 

# THUMB-specific options here
TOPT = -mthumb -DTHUMB

# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes #-Wno-sign-compare

# Define C++ warning options here
CPPWARN = -Wall -Wextra

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
DLIBS =

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

ifeq ($(USE_FWLIB),yes)
  include $(CHIBIOS)/ext/stm32lib/stm32lib.mk
  CSRC += $(STM32SRC)
  INCDIR += $(STM32INC)
  USE_OPT += -DUSE_STDPERIPH_DRIVER
endif

include $(CHIBIOS)/os/ports/GCC/ARMCMx/rules.mk


# User difined rules here
MAKE_ALL_RULE_HOOK: res_usage

res_usage: $(BUILDDIR)/$(PROJECT).map $(BUILDDIR)/$(PROJECT).bin
	./res_usage.sh	


