#include <udc.h>
#include <udi_hid.h>	// From module: USB HID Library (Device)
#include "usb.h"
#include "reg.h"

static bool flag_autorize_keyboard_events = false;
static bool report_mods_saved = false;

#define SHIFT HID_MODIFIER_LEFT_SHIFT
#define NUM_OF_KEYCODE 128
struct usb_keycode {
	uint16_t keycode;
	uint16_t modifiers;
} keycode_table[NUM_OF_KEYCODE];

void bbq10_usb_init(void)
{
	udc_start();
}

bool bbq10_udi_hid_callback_keyboard_enable(void)
{
#ifdef DEBUG
	printf("USB keyboard enabled\r\n");
#endif
	flag_autorize_keyboard_events = true;
	report_mods_saved = reg_is_bit_set(REG_ID_CFG, CFG_REPORT_MODS);
	reg_set_bit(REG_ID_CFG, CFG_REPORT_MODS);
	return true;
}

void bbq10_udi_hid_callback_keyboard_disable(void)
{
	flag_autorize_keyboard_events = false;
	if (report_mods_saved)
		reg_set_bit(REG_ID_CFG, CFG_REPORT_MODS);
	else
		reg_clear_bit(REG_ID_CFG, CFG_REPORT_MODS);
}

void bbq10_udi_hid_kbd_up(int key_id)
{
	if (!flag_autorize_keyboard_events) {
		return;
	}
	if (NUM_OF_KEYCODE <= key_id || key_id <= 0) {
#ifdef DEBUG
		printf("Ignore key_id = %d (too large)\r\n", key_id);
#endif
	}

	uint16_t keycode = keycode_table[key_id].keycode;
	uint16_t mods = keycode_table[key_id].modifiers;
	if (keycode == 0 && mods != 0) {
		udi_hid_kbd_modifier_up(mods);
		return;
	}
	udi_hid_kbd_up(keycode);
	if (mods & SHIFT)
		udi_hid_kbd_modifier_up(HID_MODIFIER_LEFT_SHIFT);
}

void bbq10_udi_hid_kbd_down(int key_id)
{
	if (!flag_autorize_keyboard_events) {
		return;
	}
	if (NUM_OF_KEYCODE <= key_id || key_id <= 0) {
#ifdef DEBUG
		printf("Ignore key_id = %d (too large)\r\n", key_id);
#endif
	}

	uint16_t keycode = keycode_table[key_id].keycode;
	uint16_t mods = keycode_table[key_id].modifiers;
	if (keycode == 0 && mods != 0) {
		udi_hid_kbd_modifier_down(mods);
		return;
	}
	if (mods & SHIFT)
		udi_hid_kbd_modifier_down(HID_MODIFIER_LEFT_SHIFT);
	udi_hid_kbd_down(keycode);
}

struct usb_keycode keycode_table[NUM_OF_KEYCODE] = {
	['\b'] = { HID_BACKSPACE },
	['\t'] = { HID_TAB },
	['\n'] = { HID_ENTER },
	[19] = { .modifiers = HID_MODIFIER_LEFT_CTRL },
	[' '] = { HID_SPACEBAR },
	['!'] = { HID_1, SHIFT },
	['"'] = { HID_QUOTE, SHIFT },
	['#'] = { HID_3, SHIFT },
	['$'] = { HID_4, SHIFT },
	['%'] = { HID_5, SHIFT },
	['&'] = { HID_7, SHIFT },
	['\''] = { HID_QUOTE },
	['('] = { HID_9, SHIFT },
	[')'] = { HID_0, SHIFT },
	['*'] = { HID_8, SHIFT },
	['+'] = { HID_PLUS, SHIFT },
	[','] = { HID_COMMA },
	['-'] = { HID_UNDERSCORE },
	['.'] = { HID_DOT },
	['/'] = { HID_SLASH },
	['0'] = { HID_0 },
	['1'] = { HID_1 },
	['2'] = { HID_2 },
	['3'] = { HID_3 },
	['4'] = { HID_4 },
	['5'] = { HID_5 },
	['6'] = { HID_6 },
	['7'] = { HID_7 },
	['8'] = { HID_8 },
	['9'] = { HID_9 },
	[':'] = { HID_COLON, SHIFT },
	[';'] = { HID_COLON },
	['<'] = { HID_COMMA, SHIFT },
	['='] = { HID_PLUS },
	['>'] = { HID_DOT, SHIFT },
	['@'] = { HID_2, SHIFT },
	['A'] = { HID_A, SHIFT },
	['B'] = { HID_B, SHIFT },
	['C'] = { HID_C, SHIFT },
	['D'] = { HID_D, SHIFT },
	['E'] = { HID_E, SHIFT },
	['F'] = { HID_F, SHIFT },
	['G'] = { HID_G, SHIFT },
	['H'] = { HID_H, SHIFT },
	['I'] = { HID_I, SHIFT },
	['J'] = { HID_J, SHIFT },
	['K'] = { HID_K, SHIFT },
	['L'] = { HID_L, SHIFT },
	['M'] = { HID_M, SHIFT },
	['N'] = { HID_N, SHIFT },
	['O'] = { HID_O, SHIFT },
	['P'] = { HID_P, SHIFT },
	['Q'] = { HID_Q, SHIFT },
	['R'] = { HID_R, SHIFT },
	['S'] = { HID_S, SHIFT },
	['T'] = { HID_T, SHIFT },
	['U'] = { HID_U, SHIFT },
	['V'] = { HID_V, SHIFT },
	['W'] = { HID_W, SHIFT },
	['X'] = { HID_X, SHIFT },
	['Y'] = { HID_Y, SHIFT },
	['Z'] = { HID_Z, SHIFT },
	['['] = { HID_OPEN_BRACKET },
	['\\'] = { HID_BACKSLASH },
	[']'] = { HID_CLOSE_BRACKET },
	['^'] = { HID_6, SHIFT },
	['_'] = { HID_UNDERSCORE, SHIFT },
	['`'] = { HID_TILDE },
	['a'] = { HID_A },
	['b'] = { HID_B },
	['c'] = { HID_C },
	['d'] = { HID_D },
	['e'] = { HID_E },
	['f'] = { HID_F },
	['g'] = { HID_G },
	['h'] = { HID_H },
	['i'] = { HID_I },
	['j'] = { HID_J },
	['k'] = { HID_K },
	['l'] = { HID_L },
	['m'] = { HID_M },
	['n'] = { HID_N },
	['o'] = { HID_O },
	['p'] = { HID_P },
	['q'] = { HID_Q },
	['r'] = { HID_R },
	['s'] = { HID_S },
	['t'] = { HID_T },
	['u'] = { HID_U },
	['v'] = { HID_V },
	['w'] = { HID_W },
	['x'] = { HID_X },
	['y'] = { HID_Y },
	['z'] = { HID_Z },
	['{'] = { HID_OPEN_BRACKET, SHIFT },
	['|'] = { HID_BACKSLASH, SHIFT },
	['}'] = { HID_CLOSE_BRACKET, SHIFT },
	['?'] = { HID_SLASH, SHIFT },
	['~'] = { HID_TILDE, SHIFT },
	[127] = { HID_DELETE },
};
