#include "backlight.h"
#include "conf_target.h"
#include "reg.h"

#define PWM_USE_TCC

#ifdef PWM_USE_TCC
	/* not implemented */
#else
#include <tc.h>

static struct tc_module instance;
#endif

void backlight_update(void)
{
#ifdef PWM_USE_TCC
	/* not implemented */
#else
	tc_set_compare_value(&instance, PWM_CHANNEL, reg_get_value(REG_ID_BKL) * 0xFF);
#endif
}

void backlight_init(void)
{
#ifdef PWM_USE_TCC
	/* not implemented */
#else
	struct tc_config config;
	tc_get_config_defaults(&config);

	config.counter_size    = TC_COUNTER_SIZE_16BIT;
	config.wave_generation = TC_WAVE_GENERATION_NORMAL_PWM;
	config.counter_16_bit.compare_capture_channel[PWM_CHANNEL] = reg_get_value(REG_ID_BKL) * 0xFF;

	config.pwm_channel[PWM_CHANNEL].enabled = true;
	config.pwm_channel[PWM_CHANNEL].pin_out = PWM_OUT_PIN;
	config.pwm_channel[PWM_CHANNEL].pin_mux = PWM_OUT_MUX;

	while (tc_init(&instance, PWM_MODULE, &config) != STATUS_OK) { }
	tc_enable(&instance);
#endif /*  PWM_USE_TCC */
}
