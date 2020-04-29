#include "led.h"

#include <port.h>

static void bbq10_led_init_pin(int pin)
{
	struct port_config port_init;
	port_get_config_defaults(&port_init);

	port_init.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(pin, &port_init);
	port_pin_set_output_level(pin, 0);
}

void bbq10_led_init(void)
{
#ifdef DEBUG
	printf("Initialize LEDs\r\n");
#endif
	bbq10_led_init_pin(BBQ10_LED_CAPSLOCK_PIN);
	bbq10_led_init_pin(BBQ10_LED_NUMLOCK_PIN);
}

void bbq10_led_set(int led, int value)
{
	switch (led) {
	case BBQ10_LED_CAPSLOCK:
		port_pin_set_output_level(BBQ10_LED_CAPSLOCK_PIN, !!value);
		break;
	case BBQ10_LED_NUMLOCK:
		port_pin_set_output_level(BBQ10_LED_NUMLOCK_PIN, !!value);
		break;
	default:
		printf("%s: Unknown LED %d\r\n", __func__, led);
		break;
	}
}
