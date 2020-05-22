CROSS_COMPILE ?= arm-none-eabi-
TARGET        ?= stm32l053

CC      := $(CROSS_COMPILE)gcc
LD      := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
SIZE    := $(CROSS_COMPILE)size

include targets/$(TARGET)/target.mk

SAMD          ?= samd20
SAMD_I2C      ?= $(SAMD)
SAMD_CLOCK    ?= $(SAMD)

SRCS += \
	targets/$(TARGET)/target.c \
	app/backlight.c \
	app/fifo.c \
	app/i2c.c \
	app/keyboard.c \
	app/main.c \
	app/reg.c \
	app/time.c \

INCS += \
	targets/$(TARGET) \
	targets \
	app/config \

DEFS += \
	I2C_SLAVE_CALLBACK_MODE=true \
	CYCLE_MODE

LIBS += \

ifeq ($(BBQ10_DEBUG_ENABLE),true)
DEFS += \
	DEBUG \

endif

ifeq ($(BBQ10_USB_ENABLE),true)
SRCS += \
	app/usb.c \

INCS += \

DEFS += \
	BBQ10_USB_ENABLE \
	BOARD=USER_BOARD \

endif

ifeq ($(BBQ10_LED_ENABLE),true)
SRCS += \
	app/led.c \

DEFS += \
	BBQ10_LED_ENABLE \

endif

OBJS := $(patsubst %.c,out/$(TARGET)/obj/%.c.o, $(filter %.c, $(SRCS)))
DEPS := $(patsubst %.o,%.d,$(OBJS))
LDSCRIPT := libopencm3/lib/ \
	libopencm3/lib/stm32/l0/

CFLAGS := \
	-mcpu=cortex-m0plus -mthumb \
	-std=gnu99 -Os -g -Wall -Wextra \
	-Wno-missing-field-initializers -Wno-unused-parameter -Wno-expansion-to-defined \
	-ffunction-sections -fdata-sections -fomit-frame-pointer \
	$(addprefix -D, $(DEFS)) \
	$(addprefix -I, $(INCS))

LDFLAGS := \
	-mcpu=cortex-m0plus -mthumb \
	-Wl,--gc-sections --specs=nano.specs \
	-nostartfiles \
	$(addprefix -L, $(LDSCRIPT)) \
	$(addprefix -T, $(LD_FILE)) \
	$(LIBS)

all: out/$(TARGET)/app.bin
.PHONY: all

out/$(TARGET)/obj/%.c.o: %.c
	@echo "CC $<"
	@mkdir -p $(dir $@)
	@$(CC) -MM -MF $(subst .o,.d,$@) -MP -MT "$@ $(subst .o,.d,$@)" $(CFLAGS) $<
	@$(CC) $(CFLAGS) -c -o $@ $<

out/$(TARGET)/app.elf: $(OBJS)
	@echo "LD $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -Xlinker -Map=$@.map
	@$(SIZE) $@

%.bin: %.elf
	@$(OBJCOPY) -O binary $< $@

clean:
	@echo "Removing the out directory"
	@rm -rf out/
.PHONY: clean

flash: out/$(TARGET)/app.bin
	@echo -e "reset halt\nprogram $< verify\nreset run\nexit\n" | nc localhost 4444
.PHONY: flash

daplink:
	@openocd \
	-f interface/cmsis-dap.cfg \
	-c "transport select swd" \
	-f target/at91samdXX.cfg \
	-c "init ; reset halt"
.PHONY: daplink

stlink:
	@openocd \
	-f interface/stlink-v2.cfg \
	-f target/at91samdXX.cfg \
	-c "init ; reset halt"
.PHONY: stlink

jlink:
	@openocd \
	-f interface/jlink.cfg \
	-c "transport select swd" \
	-c "set WORKAREASIZE 0" \
	-f target/at91samdXX.cfg \
	-c "init ; reset halt"
.PHONY: jlink

ifneq ("$(MAKECMDGOALS)","clean")
-include $(DEPS)
endif
