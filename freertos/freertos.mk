FREERTOS_DIR = freertos/FreeRTOS-Kernel

FREERTOS_INC =  -I$(FREERTOS_DIR)/include \
		-I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F \
		-I$(CONFIG_DIR)

FREERTOS_SRC =  tasks.c queue.c list.c \
		portable/GCC/ARM_CM4F/port.c \
		portable/MemMang/heap_3.c
FREERTOS_SRC := $(addprefix $(FREERTOS_DIR)/, $(FREERTOS_SRC))

FREERTOS_OBJ = build/freertos.o

freertos: $(FREERTOS_OBJ)

$(FREERTOS_OBJ): $(FREERTOS_SRC)
	@echo "\033[0;32mCompiling FreeRTOS...\033[0m"
	@$(GCC) $^ -o $@ -r $(CFLAGS) $(FREERTOS_INC)
