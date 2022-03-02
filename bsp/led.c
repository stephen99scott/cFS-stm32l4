#include "led.h"

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"

#define LED_GREEN_PIN  LL_GPIO_PIN_8
#define LED_GREEN_PORT GPIOE
#define LED_RED_PIN    LL_GPIO_PIN_2
#define LED_RED_PORT   GPIOB

void led_init(void)
{
  /* Init red LED */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

  LL_GPIO_InitTypeDef config = { 0 };

  config.Pin = LED_RED_PIN;
  config.Mode = LL_GPIO_MODE_OUTPUT;
  config.Speed = LL_GPIO_SPEED_FREQ_LOW;
  config.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  config.Pull = LL_GPIO_PULL_UP;

  LL_GPIO_Init(LED_RED_PORT, &config);

  /* Init green LED */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);

  config.Pin = LED_GREEN_PIN;
  config.Mode = LL_GPIO_MODE_OUTPUT;
  config.Speed = LL_GPIO_SPEED_FREQ_LOW;
  config.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  config.Pull = LL_GPIO_PULL_UP;

  LL_GPIO_Init(LED_GREEN_PORT, &config);

  LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_8);
}

void led_set(led_t led, led_state_t state)
{
  uint32_t pin = 0;
  GPIO_TypeDef *port = 0;

  switch (led)
  {
  	case LED_GREEN:
  	  pin = LED_GREEN_PIN;
  	  port = LED_GREEN_PORT;
  	  break;
  	case LED_RED:
  	  pin = LED_RED_PIN;
  	  port = LED_RED_PORT;
  	  break;
  }

  switch (state)
  {
	case LED_OFF:
	  LL_GPIO_ResetOutputPin(port, pin);
	  break;
	case LED_ON:
	  LL_GPIO_SetOutputPin(port, pin);
	  break;
  }
}

void led_toggle(led_t led)
{
  uint32_t pin = 0;
  GPIO_TypeDef *port = 0;

  switch (led)
  {
  	case LED_GREEN:
  	  pin = LED_GREEN_PIN;
  	  port = LED_GREEN_PORT;
  	  break;
  	case LED_RED:
  	  pin = LED_RED_PIN;
  	  port = LED_RED_PORT;
  	  break;
  }

  LL_GPIO_TogglePin(port, pin);
}
