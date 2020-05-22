// #include <delay/delay.h>
// #include <usart/usart.h>

#include "backlight.h"
#include "fifo.h"
#include "i2c.h"
#include "reg.h"
#include "target.h"
#include "time.h"
#include "usb.h"
#include "led.h"

//#define DEBUG_SOFT_SERIAL
//#define DEBUG_SOFT_SERIAL_PIN PIN_PA16

#ifdef DEBUG
#ifndef DEBUG_SOFT_SERIAL
static struct usart_module usart_instance;
#endif
#endif

#ifdef DEBUG
#ifdef DEBUG_SOFT_SERIAL
void debug_out_byte(int c)
{
	int i;
	int pin = DEBUG_SOFT_SERIAL_PIN;
	int delay = 20; /* magic number for 9600 baud */
	int parity = 0;

	/* start bit */
	port_pin_set_output_level(pin, 0);
	delay_us(delay);

	/* send byte */
	for (i = 0; i < 8; i++) {
		port_pin_set_output_level(pin, (c & (0x01 << i)) ? 1 : 0);
		parity += ((c & (0x01 << i)) ? 1 : 0);
		delay_us(delay);
	}

#if 0
	/* parity bit */
	port_pin_set_output_level(pin, (parity % 2) ? 1 : 0);
	delay_us(delay);
#endif

	/* stop bit */
	port_pin_set_output_level(pin, 1);
	delay_us(delay);
}

int debug_out(const char *msg, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		debug_out_byte(msg[i]);
	}

	return len;
}
#endif /* DEBUG_SOFT_SERIAL */

static void configure_usart(void)
{
// #ifdef DEBUG_SOFT_SERIAL
// 	struct port_config port_init;
// 	port_get_config_defaults(&port_init);

// 	port_init.direction = PORT_PIN_DIR_OUTPUT;
// 	port_pin_set_config(DEBUG_SOFT_SERIAL_PIN, &port_init);

// 	port_pin_set_output_level(DEBUG_SOFT_SERIAL_PIN, 1);
// 	delay_ms(100);
// #else
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = 115200;
	config_usart.mux_setting = CONF_UART_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = CONF_UART_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = CONF_UART_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = CONF_UART_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = CONF_UART_SERCOM_PINMUX_PAD3;

	while (usart_init(&usart_instance, CONF_UART_MODULE, &config_usart) != STATUS_OK) { }
	usart_enable(&usart_instance);
// #endif /* DEBUG_SOFT_SERIAL */
}

int _write(void *fd, const char *msg, size_t len)
{
#ifdef DEBUG_SOFT_SERIAL
	debug_out(msg, len);
#else
	usart_write_buffer_wait(&usart_instance, (const uint8_t*)msg, len);
#endif

	return len;
}

int _read(void *fd, char *msg, size_t len)
{
#ifdef DEBUG_SOFT_SERIAL
	/* not implemented */
#else
	usart_read_buffer_wait(&usart_instance, (uint8_t *)msg, len);
#endif

	return len;
}
#endif

static void key_cb(char key, enum key_state state)
{
	bool do_int = false;

	if (reg_is_bit_set(REG_ID_CFG, CFG_KEY_INT)) {
		reg_set_bit(REG_ID_INT, INT_KEY);
		do_int = true;
	}

#ifdef DEBUG
	printf("key: 0x%02X/%d/%c, state: %d, blk: %d\r\n", key, key, key, state, reg_get_value(REG_ID_BKL));
#endif
	if (state == KEY_STATE_PRESSED) {
		bbq10_udi_hid_kbd_down(key);
	} else
	if (state == KEY_STATE_RELEASED) {
		bbq10_udi_hid_kbd_up(key);
	}

	const struct fifo_item item = { key, state };
	if (!fifo_enqueue(item)) {
		if (reg_is_bit_set(REG_ID_CFG, CFG_OVERFLOW_INT)) {
			reg_set_bit(REG_ID_INT, INT_OVERFLOW);
			do_int = true;
		}

		if (reg_is_bit_set(REG_ID_CFG, CFG_OVERFLOW_ON))
			fifo_enqueue_force(item);
	}

	if (do_int) {
		port_pin_set_output_level(int_pin, 0);
		delay_ms(INT_DURATION_MS);
		port_pin_set_output_level(int_pin, 1);
	}
}

static void lock_cb(bool caps_changed, bool num_changed)
{
	bool do_int = false;

	bbq10_led_set(BBQ10_LED_CAPSLOCK, keyboard_get_capslock());
	bbq10_led_set(BBQ10_LED_NUMLOCK, keyboard_get_numlock());

	if (caps_changed && reg_is_bit_set(REG_ID_CFG, CFG_CAPSLOCK_INT)) {
		reg_set_bit(REG_ID_INT, INT_CAPSLOCK);
		do_int = true;
	}

	if (num_changed && reg_is_bit_set(REG_ID_CFG, CFG_NUMLOCK_INT)) {
		reg_set_bit(REG_ID_INT, INT_NUMLOCK);
		do_int = true;
	}

#ifdef DEBUG
	printf("lock, caps_c: %d, caps: %d, num_c: %d, num: %d\r\n",
		   caps_changed, keyboard_get_capslock(),
		   num_changed, keyboard_get_numlock());
#endif

	if (do_int) {
		port_pin_set_output_level(int_pin, 0);
		delay_ms(INT_DURATION_MS);
		port_pin_set_output_level(int_pin, 1);
	}
}

static void config_int_pin(void)
{
	// struct port_config port_init;
	// port_get_config_defaults(&port_init);

	// port_init.direction = PORT_PIN_DIR_OUTPUT;
	// port_pin_set_config(int_pin, &port_init);
	// port_pin_set_output_level(int_pin, 1);
}

int main(void)
{
	// TODO: system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);

	system_init();
	delay_init();
	time_init();

#ifdef DEBUG
	configure_usart();
	printf("Initializing...\r\n");
#endif

	config_int_pin();
	reg_init();
	backlight_init();

	keyboard_init();
	keyboard_set_key_callback(key_cb);
	keyboard_set_lock_callback(lock_cb);

	i2c_init();
	bbq10_usb_init();
	bbq10_led_init();

#ifdef DEBUG
	printf("Starting main loop\r\n");
#endif

	while (true) {
		keyboard_process();
	}

	return 0;
}


int reset_handler(void)
{
    return main();
}


inline bool port_pin_get_input_level(void)
{return 0;}

inline bool port_pin_get_output_level(void)
{return 0;}

void delay_ms(uint32_t n){};

inline void port_pin_set_output_level(
    const uint8_t gpio_pin,
    const bool level)
{};

void system_init(void){};

// system_init
void delay_init(void){};
void i2c_init(void){};
// void time_init(void){};
// system_cpu_clock_get_hz
// SysTick_Config

uint32_t SysTick_Config(uint32_t ticks){};
