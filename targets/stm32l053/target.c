#include "target.h"

#define PIN_PA00 00
#define PIN_PA01 01
#define PIN_PA02 02
#define PIN_PA03 03
#define PIN_PA04 04
#define PIN_PA05 05
#define PIN_PA06 06
#define PIN_PA07 07
#define PIN_PA08 08
#define PIN_PA09 09
#define PIN_PA10 10
#define PIN_PA11 11
#define PIN_PA12 12
#define PIN_PA13 13
#define PIN_PA14 14
#define PIN_PA15 15
#define PIN_PA16 16
#define PIN_PA17 17
#define PIN_PA18 18
#define PIN_PA19 19
#define PIN_PA20 20
#define PIN_PA21 21
#define PIN_PA22 22
#define PIN_PA23 23
#define PIN_PA24 24
#define PIN_PA25 25
#define PIN_PA26 26
#define PIN_PA27 27
#define PIN_PA28 28
#define PIN_PA29 29
#define PIN_PA30 30
#define PIN_PA31 31
#define PIN_PA32 32



const uint8_t row_pins[NUM_OF_ROWS] =
{
	PIN_PA14, // KBD_ROW1
	PIN_PA16, // KBD_ROW2
	PIN_PA22, // KBD_ROW3
	PIN_PA24, // KBD_ROW4
	PIN_PA25, // KBD_ROW5
	PIN_PA27, // KBD_ROW6
	PIN_PA28, // KBD_ROW7
};

const uint8_t col_pins[NUM_OF_COLS] =
{
	PIN_PA15, // KBD_COL1
	PIN_PA17, // KBD_COL2
	PIN_PA18, // KBD_COL3
	PIN_PA19, // KBD_COL4
	PIN_PA23, // KBD_COL5
};

const uint8_t btn_pins[NUM_OF_BTNS] =
{
	PIN_PA01, // JOY_UP
	PIN_PA05, // JOY_DOWN
	PIN_PA03, // JOY_LEFT
	PIN_PA04, // JOY_RIGHT
	PIN_PA02, // JOY_CENTER
	PIN_PA00, // BTN_LEFT
	PIN_PA06, // BTN_RIGHT
};

const uint8_t int_pin = PIN_PA10;

const uint8_t kbd_bl_pin = PIN_PA11;
