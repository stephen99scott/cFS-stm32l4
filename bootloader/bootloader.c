#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_utils.h"

static void sysclk_init(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_1);

  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_MSI_Enable();

  while(LL_RCC_MSI_IsReady() != 1);

  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);
  LL_RCC_MSI_SetCalibTrimming(0);

  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 20, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_EnableDomain_SYS();
  LL_RCC_PLL_Enable();

  while(LL_RCC_PLL_IsReady() != 1);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  LL_Init1msTick(20000000);

  LL_SetSystemCoreClock(20000000);
}

static void bringup(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  sysclk_init();
}

int main(void)
{
  bringup();

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);

  LL_GPIO_InitTypeDef config = { 0 };

  config.Pin = LL_GPIO_PIN_8;
  config.Mode = LL_GPIO_MODE_OUTPUT;
  config.Speed = LL_GPIO_SPEED_FREQ_LOW;
  config.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  config.Pull = LL_GPIO_PULL_UP;

  LL_GPIO_Init(GPIOE, &config);

  LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_8);



  // MX_GPIO_Init();
  // MX_USART2_UART_Init();

  // HAL_GPIO_WritePin(LD_G_GPIO_Port, LD_G_Pin, GPIO_PIN_SET);
  // while (1)
  // {

  // }
  return 0;
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {

  }
}
