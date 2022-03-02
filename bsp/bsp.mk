BSP_DIR = bsp

DRIVERS_DIR = $(BSP_DIR)/STM32CubeL4/Drivers
HAL_DIR = $(DRIVERS_DIR)/STM32L4xx_HAL_Driver
CMSIS_DIR = $(DRIVERS_DIR)/CMSIS
DEVICE_DIR = $(CMSIS_DIR)/Device/ST/STM32L4xx

BSP_INC = 	-I$(BSP_DIR) \
			-I$(HAL_DIR)/Inc \
			-I$(CMSIS_DIR)/Include \
			-I$(DEVICE_DIR)/Include

SYMBOLS = -DSTM32L476xx -DUSE_FULL_LL_DRIVER

HAL_SRC = \
	$(HAL_DIR)/Src/stm32l4xx_ll_gpio.c \
	$(HAL_DIR)/Src/stm32l4xx_ll_utils.c

BSP_SRC =   $(HAL_SRC) \
			$(BSP_DIR)/system_stm32l4xx.c \
			$(BSP_DIR)/led.c

BSP_OBJS = $(notdir $(BSP_SRC:%.c=%.o))

BSP_OBJ = build/bsp.o

bsp: $(BSP_OBJ)

$(BSP_OBJ): $(BSP_SRC)
	@echo "\033[0;32mCompiling BSP...\033[0m"
	@$(GCC) $^ -o $@ -r $(CFLAGS) $(SYMBOLS) $(BSP_INC)
