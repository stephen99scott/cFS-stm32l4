#ifndef LED_H
#define LED_H

typedef enum 
{
	LED_OFF,
	LED_ON
} led_state_t;

typedef enum
{
	LED_GREEN,
	LED_RED
} led_t;

void led_init(void);

void led_set(led_t led, led_state_t state);

void led_toggle(led_t led);

#endif /* LED_H */
