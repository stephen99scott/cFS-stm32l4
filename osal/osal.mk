OSAL_DIR = osal

OSAL_SHARED_DIR = $(OSAL_DIR)/shared
OSAL_FREERTOS_DIR = $(OSAL_DIR)/freertos

OSAL_INC =  -I$(OSAL_FREERTOS_DIR)/inc \
			-I$(OSAL_SHARED_DIR)/inc \
			-I$(OSAL_DIR)/inc \
			-I$(CONFIG_DIR)

OSAL_FREERTOS_SRC = \
	$(OSAL_FREERTOS_DIR)/src/os-impl-binsem.c \
	$(OSAL_FREERTOS_DIR)/src/os-impl-common.c \
	$(OSAL_FREERTOS_DIR)/src/os-impl-countsem.c

OSAL_SRC =  $(OSAL_SHARED_SRC) $(OSAL_FREERTOS_SRC)

OSAL_OBJS = $(notdir $(OSAL_SRC:%.c=%.o))

OSAL_OBJ = build/osal.o

osal: $(OSAL_OBJ)

$(OSAL_OBJ): $(OSAL_SRC)
	@echo "\033[0;32mCompiling OSAL...\033[0m"
	@$(GCC) $^ -o $@ -r $(CFLAGS) $(OSAL_INC) $(FREERTOS_INC)
