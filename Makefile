# put your *.c source files here, make should handle the rest!
SRCS=main.c

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)
PROJ_NAME=main

# Target MCU. STM32F40_41xxx / STM32F427_437xx / STM32F429_439xx / STM32F401xx
# See */CMSIS/Device/ST/*/stm32f*.h
MCU=STM32F401xx

###################################################

# Build artifact location
BUILD_DIR=build

# External libraries
LIBRARIES = lib

# Libraries from ST / ARM
ST_FIRMWARE = $(LIBRARIES)/STM32F401-Discovery_FW_V1.0.0

CMSIS = $(ST_FIRMWARE)/Libraries/CMSIS
STD_PERIPH_DRIVER = $(ST_FIRMWARE)/STM32F4xx_StdPeriph_Driver

###################################################

# Location of linker scripts. Linker script is $(MCU).ld
LINKER_SCRIPT_DIR = $(LIBRARIES)/linker

STARTUP_SCRIPT = $(CMSIS)/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f401xx.s

###################################################

CC=arm-none-eabi-gcc
GDB=arm-none-eabi-gdb
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

# SRCS   += $(ST_FIRMWARE)/system_stm32f4xx.c

CFLAGS  = -Wall -g -std=c99 -Os  
CFLAGS += -mlittle-endian -mcpu=cortex-m4  -march=armv7e-m -mthumb
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -ffunction-sections -fdata-sections

LDFLAGS += -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(PROJ_NAME).map

###################################################

vpath %.a $(STD_PERIPH_LIB)

ROOT=$(shell pwd)

CFLAGS += -D $(MCU)
CFLAGS += -L $(ST_FIRMWARE)
CFLAGS += -I inc 
CFLAGS += -I src
CFLAGS += -I $(CMSIS)/Include
CFLAGS += -I $(CMSIS)/Device/ST/STM32F4xx/Include
CFLAGS += -I $(ST_FIRMWARE)
CFLAGS += -I $(ST_FIRMWARE)/Libraries/stm32f4xx_StdPeriph_Driver/inc
CFLAGS += -I $(ST_FIRMWARE)/Utilities/STM32F401-Discovery
# CFLAGS += -I $(ST_FIRMWARE)/Libraries/STM32_USB_Device_Library/Core/inc
# CFLAGS += -I $(ST_FIRMWARE)/Libraries/STM32_USB_Device_Library/Class/audio/inc
# CFLAGS += -I $(ST_FIRMWARE)/Libraries/STM32_USB_Device_Library/Class/cdc/inc
# CFLAGS += -I $(ST_FIRMWARE)/Libraries/STM32_USB_Device_Library/Class/dfu/inc
# CFLAGS += -I $(ST_FIRMWARE)/Libraries/STM32_USB_Device_Library/Class/hid/inc
# CFLAGS += -I $(ST_FIRMWARE)/Libraries/STM32_USB_Device_Library/Class/msc/inc
#CFLAGS += -I $(CMSIS)/Include 
#CFLAGS += -I $(STD_PERIPH_LIB)/Libraries/STM32F4xx_StdPeriph_Driver/inc
#CFLAGS += -I $(STD_PERIPH_LIB)/Projects/Demonstration/stm32f4xx_conf.h

# SRCS += $(ST_FIRMWARE)/Utilities/STM32F401-Discovery/stm32f401_discovery.c
#SRCS += stm32f0_discovery.c stm32f0xx_it.c

OBJS = $(addprefix $(BUILD_DIR)/objs/,$(SRCS:.c=.o))
DEPS = $(addprefix $(BUILD_DIR)/deps/,$(SRCS:.c=.d))

###################################################

.PHONY: all proj program debug clean reallyclean

all: firmware proj

-include $(DEPS)

firmware: $(ST_FIRMWARE)
	$(MAKE) -C $(ST_FIRMWARE) MCU=$(MCU)

proj: $(BUILD_DIR) $(BUILD_DIR)/$(PROJ_NAME).elf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/deps $(BUILD_DIR)/objs

$(BUILD_DIR)/objs/%.o : src/%.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -MMD -MF $(BUILD_DIR)/deps/$(*F).d

$(BUILD_DIR)/$(PROJ_NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(STARTUP_SCRIPT) -lstm32f4 -T$(LINKER_SCRIPT_DIR)/$(MCU).ld
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJ_NAME).elf $(BUILD_DIR)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(PROJ_NAME).elf $(BUILD_DIR)/$(PROJ_NAME).bin
	$(OBJDUMP) -St $(BUILD_DIR)/$(PROJ_NAME).elf >$(BUILD_DIR)/$(PROJ_NAME).lst
	$(SIZE) $(BUILD_DIR)/$(PROJ_NAME).elf

program: all
	@sleep 1
	st-flash write `pwd`/$(BUILD_DIR)/$(PROJ_NAME).bin 0x08000000

debug: program
	$(GDB) -x extra/gdb_cmds $(PROJ_NAME).elf

clean:
	find ./ -name '*~' | xargs rm -f	
	rm -rf $(BUILD_DIR)

reallyclean: clean
	$(MAKE) -C $(ST_FIRMWARE) clean