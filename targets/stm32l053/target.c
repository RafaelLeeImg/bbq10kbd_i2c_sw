#include "target.h"

#include <libopencm3/stm32/gpio.h>

const uint32_t row_pins[NUM_OF_ROWS*2] =
{
	GPIOA, GPIO10, // KBD_ROW1
	GPIOA, GPIO11, // KBD_ROW2
	GPIOA, GPIO12, // KBD_ROW3
	GPIOA, GPIO13, // KBD_ROW4
	GPIOA, GPIO14, // KBD_ROW5
	GPIOA, GPIO15, // KBD_ROW6
	GPIOA, GPIO9, // KBD_ROW7
};

const uint32_t col_pins[NUM_OF_COLS*2] =
{
	GPIOB, GPIO10, // KBD_COL1
	GPIOB, GPIO11, // KBD_COL2
	GPIOB, GPIO12, // KBD_COL3
	GPIOB, GPIO13, // KBD_COL4
	GPIOB, GPIO14, // KBD_COL5
};

const uint32_t btn_pins[NUM_OF_BTNS*2] =
{
	GPIOC, GPIO10, // JOY_UP
	GPIOC, GPIO11, // JOY_DOWN
	GPIOC, GPIO12, // JOY_LEFT
	GPIOC, GPIO13, // JOY_RIGHT
	GPIOC, GPIO14, // JOY_CENTER
	GPIOC, GPIO15, // BTN_LEFT
	GPIOC, GPIO9, // BTN_RIGHT
};

const uint32_t int_pin[2] = {GPIOC, GPIO8};

const uint32_t kbd_bl_pin[2] = {GPIOC, GPIO7};
