CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar

# Build artifact location
BUILD_DIR=build
###########################################

vpath %.c Libraries/STM32F4xx_StdPeriph_Driver/src

CFLAGS  = -g -O2 -Wall
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -march=armv7e-m
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS += -ffreestanding -nostdlib
CFLAGS += -include stm32f4xx_conf.h 
CFLAGS += -I Libraries/CMSIS/Include 
CFLAGS += -I Libraries/CMSIS/Device/ST/STM32F4xx/Include 
CFLAGS += -I Libraries/STM32F4xx_StdPeriph_Driver/inc
CFLAGS += -I Libraries/STM32_USB_Device_Library/Core/inc
CFLAGS += -I Libraries/STM32_USB_Device_Library/Class/audio/inc
CFLAGS += -I Libraries/STM32_USB_Device_Library/Class/cdc/inc
CFLAGS += -I Libraries/STM32_USB_Device_Library/Class/dfu/inc
CFLAGS += -I Libraries/STM32_USB_Device_Library/Class/hid/inc
CFLAGS += -I Libraries/STM32_USB_Device_Library/Class/msc/inc
CFLAGS += -D$(MCU)

SRCS = stm32f4xx_adc.c stm32f4xx_can.c \
	   stm32f4xx_crc.c \
       stm32f4xx_dac.c stm32f4xx_dbgmcu.c stm32f4xx_dma.c \
       stm32f4xx_exti.c stm32f4xx_flash.c stm32f4xx_gpio.c \
       stm32f4xx_i2c.c stm32f4xx_iwdg.c \
       stm32f4xx_pwr.c stm32f4xx_rcc.c stm32f4xx_rtc.c stm32f4xx_spi.c \
       stm32f4xx_syscfg.c stm32f4xx_tim.c stm32f4xx_usart.c \
       stm32f4xx_wwdg.c \
       system_stm32f4xx.c

OBJS = $(addprefix $(BUILD_DIR)/objs/,$(SRCS:.c=.o))
DEPS = $(addprefix $(BUILD_DIR)/deps/,$(SRCS:.c=.d))

.PHONY: all clean

all: libstm32f4.a

-include $(DEPS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/deps $(BUILD_DIR)/objs

$(BUILD_DIR)/objs/%.o : %.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -MMD -MF $(BUILD_DIR)/deps/$(*F).d

libstm32f4.a: $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	rm -f $(OBJS) $(BUILD_DIR) libstm32f4.a

