#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>


#include "backlight.h"
#include "conf_app.h"
#include "conf_target.h"
#include "fifo.h"
#include "i2c.h"
#include "keyboard.h"
#include "reg.h"
#include "util.h"

#define WRITE_MASK			(1 << 7)

static struct {
	// struct {
	// 	uint8_t reg;
	// 	uint8_t data;
	// } read_buffer;
	// struct i2c_slave_packet read_packet;

	// uint8_t write_buffer[2];
	// struct i2c_slave_packet write_packet;
} self;

static void read_request_cb(struct i2c_slave_module * const i2c_slave)
{
	// self.write_packet.data_length = sizeof(uint8_t) * ARRAY_SIZE(self.write_buffer);

	// i2c_slave_write_packet_job(i2c_slave, &self.write_packet);
}

static void read_complete_cb(struct i2c_slave_module * const i2c_slave)
{
// 	const bool is_write = (self.read_buffer.reg & WRITE_MASK);
// 	const uint8_t reg = (self.read_buffer.reg & ~WRITE_MASK);

// #ifdef DEBUG
// 	printf("read complete, is_write: %d, reg: 0x%02X\r\n", is_write, reg);
// #endif

// 	switch (reg) {
// 	case REG_ID_CFG:
// 	case REG_ID_INT:
// 	case REG_ID_DEB:
// 	case REG_ID_FRQ:
// 	case REG_ID_BKL:
// 	{
// 		if (is_write) {
// 			reg_set_value(reg, self.read_buffer.data);

// 			if (reg == REG_ID_BKL)
// 				backlight_update();
// 		} else {
// 			self.write_buffer[0] = reg_get_value(reg);
// 			self.write_packet.data_length = sizeof(uint8_t);
// 		}
// 		break;
// 	}

// 	case REG_ID_VER:
// 		self.write_buffer[0] = VER_VAL;
// 		self.write_packet.data_length = sizeof(uint8_t);
// 		break;

// 	case REG_ID_KEY:
// 		self.write_buffer[0] = fifo_count();
// 		self.write_buffer[0] |= keyboard_get_numlock()  ? KEY_NUMLOCK  : 0x00;
// 		self.write_buffer[0] |= keyboard_get_capslock() ? KEY_CAPSLOCK : 0x00;
// 		self.write_packet.data_length = sizeof(uint8_t);
// 		break;

// 	case REG_ID_FIF:
// 	{
// 		const struct fifo_item item = fifo_dequeue();

// 		self.write_buffer[0] = (uint8_t)item.state;
// 		self.write_buffer[1] = (uint8_t)item.key;
// 		self.write_packet.data_length = sizeof(uint8_t) * 2;
// 		break;
// 	}

// 	case REG_ID_RST:
// 		NVIC_SystemReset();
// 		break;
// 	}
}

static void write_request_cb(struct i2c_slave_module * const i2c_slave)
{
// 	if (i2c_slave_read_packet_job(i2c_slave, &self.read_packet) != STATUS_OK) {
// #ifdef DEBUG
// 		printf("Read failed, damnit\r\n");
// #endif
// 	}
}

void i2c_init(void)
{
	// struct i2c_slave_config config;
	// i2c_slave_get_config_defaults(&config);

	// config.address      = SLAVE_ADDRESS;
	// config.address_mode = I2C_SLAVE_ADDRESS_MODE_MASK;

	// while (i2c_slave_init(&self.instance, CONF_I2C_SLAVE_MODULE, &config) != STATUS_OK) { }
	// i2c_slave_enable(&self.instance);

	// i2c_slave_register_callback(&self.instance, read_request_cb, I2C_SLAVE_CALLBACK_READ_REQUEST);
	// i2c_slave_enable_callback(&self.instance, I2C_SLAVE_CALLBACK_READ_REQUEST);

	// i2c_slave_register_callback(&self.instance, read_complete_cb, I2C_SLAVE_CALLBACK_READ_COMPLETE);
	// i2c_slave_enable_callback(&self.instance, I2C_SLAVE_CALLBACK_READ_COMPLETE);

	// i2c_slave_register_callback(&self.instance, write_request_cb, I2C_SLAVE_CALLBACK_WRITE_REQUEST);
	// i2c_slave_enable_callback(&self.instance, I2C_SLAVE_CALLBACK_WRITE_REQUEST);

	// self.read_packet.data_length = sizeof(self.read_buffer);
	// self.read_packet.data = (uint8_t*)&self.read_buffer;

	// self.write_packet.data_length = sizeof(uint8_t) * ARRAY_SIZE(self.write_buffer);
	// self.write_packet.data = self.write_buffer;
}


static void i2c_setup(void)
{
	rcc_periph_clock_enable(RCC_I2C1);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_set_i2c_clock_hsi(I2C1);

	i2c_reset(I2C1);
	/* Setup GPIO pin GPIO_USART2_TX/GPIO9 on GPIO port A for transmit. */
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7);
	gpio_set_af(GPIOB, GPIO_AF4, GPIO6 | GPIO7);
	i2c_peripheral_disable(I2C1);
	//configure ANFOFF DNF[3:0] in CR1
	// i2c_enable_analog_filter(I2C1);
	// i2c_set_digital_filter(I2C1, 0);
	/* HSI is at 48Mhz */
	i2c_set_speed(I2C1, i2c_speed_fm_400k, 48); // I2C1 bus speed 48Mhz
	//configure No-Stretch CR1 (only relevant in slave mode)
	// i2c_enable_stretching(I2C1);
	//addressing mode
	i2c_set_7bit_addr_mode(I2C1);
	i2c_peripheral_enable(I2C1);


    // new
    i2c_set_own_7bit_slave_address(I2C1, SLAVE_ADDRESS);
}
