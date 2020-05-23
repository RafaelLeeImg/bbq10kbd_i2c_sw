#include "time.h"

// #include <clock_feature.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>
// #include <libopencm3/stm32/gpio.h>
// #include <libopencm3/cm3/nvic.h>

static volatile uint32_t uptime_ms;

void SysTick_Handler(void)
{
	++uptime_ms;
}

void time_delay_ms(uint32_t delay)
{
	const uint32_t start_ms = uptime_ms;

	while((uptime_ms - start_ms) < delay)
		;
}

uint32_t time_uptime_ms(void)
{
	return uptime_ms;
}

/*
 * Set up timer to fire every x milliseconds
 * This is a unusual usage of systick, be very careful with the 24bit range
 * of the systick counter!  You can range from 1 to 2796ms with this.
 */
static void systick_setup(int xms)
{
	/* div8 per ST, stays compatible with M3/M4 parts, well done ST */
	systick_set_clocksource(STK_CSR_CLKSOURCE_EXT);
	/* clear counter so it starts right away */
	STK_CVR = 0;

	systick_set_reload(rcc_ahb_frequency / 8 / 1000 * xms);
	systick_counter_enable();
	systick_interrupt_enable();
}

void time_init(void)
{
	/* 1ms ticks */
	systick_setup(1);
}
