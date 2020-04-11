#ifndef _APP_CONFIG_CONF_USB_H_
#define _APP_CONFIG_CONF_USB_H_

#include <compiler.h>
#include <conf_target.h>
#include "../usb.h"

#ifndef USB_DEVICE_VENDOR_ID
#define USB_DEVICE_VENDOR_ID 0x03EB
#endif
#ifndef USB_DEVICE_PRODUCT_ID
#define USB_DEVICE_PRODUCT_ID 0x0000
#endif
#ifndef USB_DEVICE_MAJOR_VERSION
#define USB_DEVICE_MAJOR_VERSION 1
#endif
#ifndef USB_DEVICE_MINOR_VERSION
#define USB_DEVICE_MINOR_VERSION 0
#endif
#define USB_DEVICE_POWER 100
#define USB_DEVICE_ATTR USB_CONFIG_ATTR_BUS_POWERED

#define UDI_HID_KBD_ENABLE_EXT() bbq10_udi_hid_callback_keyboard_enable()
#define UDI_HID_KBD_DISABLE_EXT() bbq10_udi_hid_callback_keyboard_disable()
#define UDI_HID_KBD_CHANGE_LED(value)

#include "class/hid/device/kbd/udi_hid_kbd_conf.h" // At the end of conf_usb.h file

#endif /* _APP_CONFIG_CONF_USB_H_ */
