#pragma once

#include "target.h"

#define BBQ10_LED_CAPSLOCK 0
#define BBQ10_LED_NUMLOCK 1

#ifdef BBQ10_LED_ENABLE
extern void bbq10_led_init(void);
extern void bbq10_led_set(int led, int value);
#else
#define bbq10_led_init() while(0)
#define bbq10_led_set(led, value) while(0)
#endif /* CONF_LED_ENABLE */
