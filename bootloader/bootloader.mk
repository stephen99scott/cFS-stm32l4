BOOTLOADER_DIR = bootloader

START_SRC = startup_stm32l476xx.s
START_SRC := $(addprefix $(BOOTLOADER_DIR)/, $(START_SRC))

START_OBJ = build/start.o

BOOTLOADER_SRC = bootloader.c
BOOTLOADER_SRC := $(addprefix $(BOOTLOADER_DIR)/, $(BOOTLOADER_SRC))

BOOTLOADER_OBJ = build/bootloader.o

LDSCRIPT = $(BOOTLOADER_DIR)/STM32L476VGTX_FLASH.ld

BOOTLOADER_ELF  = build/bootloader.elf
BOOTLOADER_BIN  = build/bootloader.bin
BOOTLOADER_LIST = build/bootloader.list

bootloader: $(BOOTLOADER_BIN) $(BOOTLOADER_LIST)

$(BOOTLOADER_LIST): $(BOOTLOADER_ELF)
	@$(OBJDUMP) -D $< > $@
	@echo "\033[0;33m$@ created!\033[0m"

$(BOOTLOADER_BIN): $(BOOTLOADER_ELF)
	@$(OBJCOPY) $< $@ -O binary
	@echo "\033[0;33m$@ created!\033[0m"

$(BOOTLOADER_ELF):  $(START_OBJ) $(BOOTLOADER_OBJ) build/bsp.o build/freertos.o
	@echo "\033[0;32mLinking bootloader...\033[0m"
	@$(GCC) $(LDFLAGS) $^ -T$(LDSCRIPT) -o $@

$(BOOTLOADER_OBJ): $(BOOTLOADER_SRC)
	@echo "\033[0;32mCompiling bootloader...\033[0m"
	@$(GCC) -c $< -o $@ $(CFLAGS) $(SYMBOLS) $(BSP_INC)

$(START_OBJ): $(START_SRC)
	@echo "\033[0;32mAssembling startup...\033[0m"
	@$(AS) $< -o $@ $(ASFLAGS)
