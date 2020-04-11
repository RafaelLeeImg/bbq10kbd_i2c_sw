#pragma once

#ifdef BBQ10_USB_ENABLE
extern void bbq10_usb_init(void);
extern bool bbq10_udi_hid_callback_keyboard_enable(void);
extern void bbq10_udi_hid_callback_keyboard_disable(void);
extern void bbq10_udi_hid_kbd_modifier_up(int key_id);
extern void bbq10_udi_hid_kbd_modifier_down(int key_id);
extern void bbq10_udi_hid_kbd_up(int key_id);
extern void bbq10_udi_hid_kbd_down(int key_id);
#else
#define bbq10_usb_init() while(0)
#define bbq10_udi_hid_callback_keyboard_enable() while(0)
#define bbq10_udi_hid_callback_keyboard_disable() while(0)
#define bbq10_udi_hid_kbd_modifier_up(key_id) while(0)
#define bbq10_udi_hid_kbd_modifier_down(key_id) while(0)
#define bbq10_udi_hid_kbd_up(key_id) while(0)
#define bbq10_udi_hid_kbd_down(key_id) while(0)
#endif /* CONF_USB_ENABLE */
