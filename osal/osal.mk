OSAL_DIR = osal

OSAL_OS_DIR = $(OSAL_DIR)/os
OS_SHARED_DIR = $(OSAL_OS_DIR)/shared
OS_FREERTOS_DIR = $(OSAL_OS_DIR)/freertos
OS_PORTABLE_DIR = $(OSAL_OS_DIR)/portable

OSAL_BSP_DIR = $(OSAL_DIR)/bsp
BSP_SHARED_DIR = $(OSAL_BSP_DIR)/shared
BSP_FREERTOS_DIR = $(OSAL_BSP_DIR)/freertos

OSAL_INC =  -I$(OS_FREERTOS_DIR)/inc \
			-I$(OS_SHARED_DIR)/inc \
			-I$(BSP_SHARED_DIR)/inc \
			-I$(OSAL_OS_DIR)/inc \
			-I$(CONFIG_DIR)

OSAL_IMPL_SRC = \
	$(OS_FREERTOS_DIR)/src/os-impl-binsem.c \
	$(OS_FREERTOS_DIR)/src/os-impl-common.c \
	$(OS_FREERTOS_DIR)/src/os-impl-countsem.c \
	$(OS_PORTABLE_DIR)/os-impl-no-loader.c \
	$(OS_PORTABLE_DIR)/os-impl-no-network.c \
	$(OS_PORTABLE_DIR)/os-impl-no-shell.c \
	$(OS_PORTABLE_DIR)/os-impl-no-sockets.c \
	$(OS_PORTABLE_DIR)/os-impl-no-symtab.c

OSAL_SRC =  $(shell find $(OS_SHARED_DIR)/src -name '*.c')

OSAL_OBJ = build/osal.o

osal: $(OSAL_OBJ)

$(OSAL_OBJ): $(OSAL_SRC) $(OSAL_IMPL_SRC)
	@echo "\033[0;32mCompiling OSAL...\033[0m"
	@$(GCC) $^ -o $@ -r $(CFLAGS) $(OSAL_INC) $(FREERTOS_INC)
