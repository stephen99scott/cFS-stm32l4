include bootloader/bootloader.mk
include bsp/bsp.mk
include freertos/freertos.mk
include osal/osal.mk

TOOLCHAIN = arm-none-eabi

AS = $(TOOLCHAIN)-as
GCC = $(TOOLCHAIN)-gcc
LD = $(TOOLCHAIN)-ld
OBJCOPY = $(TOOLCHAIN)-objcopy
OBJDUMP = $(TOOLCHAIN)-objdump

CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16 -mfloat-abi=hard
MCU = $(CPU) $(FPU) -mthumb 
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding $(MCU) $(DEBUG)
ASFLAGS = --warn --fatal-warnings $(CPU) $(DEBUG)
LDFLAGS = --specs=nosys.specs $(MCU)

BUILD_DIR = build
CONFIG_DIR = config

all: bootloader

prep:
	mkdir -p $(BUILD_DIR)	

debug: DEBUG = -g
debug: all
	openocd -f board/stm32l4discovery.cfg

flash: build/bootloader.bin
	openocd -f board/stm32l4discovery.cfg \
	-c "program $< verify reset exit 0x08000000"

clean:
	@find . -maxdepth 2 -name '*.o' -exec rm {} \;
	@find . -maxdepth 2 -name '*.elf' -exec rm {} \;
	@find . -maxdepth 2 -name '*.list' -exec rm {} \;
	@find . -maxdepth 2 -name '*.bin' -exec rm {} \;

distclean:
	rm -rf build
