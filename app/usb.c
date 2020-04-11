#include <udc.h>
#include <udi_hid.h>	// From module: USB HID Library (Device)
#include "usb.h"

static bool flag_autorize_keyboard_events = false;

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
	return true;
}

void bbq10_udi_hid_callback_keyboard_disable(void)
{
	flag_autorize_keyboard_events = false;
}

void bbq10_udi_hid_kbd_modifier_up(int key_id)
{
	if (!flag_autorize_keyboard_events) {
		return;
	}
	udi_hid_kbd_up(HID_B);
}

void bbq10_udi_hid_kbd_modifier_down(int key_id)
{
	if (!flag_autorize_keyboard_events) {
		return;
	}
	udi_hid_kbd_down(HID_B);
}

void bbq10_udi_hid_kbd_up(int key_id)
{
	if (!flag_autorize_keyboard_events) {
		return;
	}
	udi_hid_kbd_up(HID_A);
}

void bbq10_udi_hid_kbd_down(int key_id)
{
	if (!flag_autorize_keyboard_events) {
		return;
	}
	udi_hid_kbd_down(HID_A);
}
