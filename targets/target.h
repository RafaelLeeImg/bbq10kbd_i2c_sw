#pragma once

#include "conf_target.h"

#include <stdint.h>

extern const uint32_t row_pins[NUM_OF_ROWS*2];
extern const uint32_t col_pins[NUM_OF_COLS*2];

#if NUM_OF_BTNS > 0
extern const uint32_t btn_pins[NUM_OF_BTNS*2];
#endif

extern const uint32_t int_pin[2];
extern const uint32_t kbd_bl_pin[2];
