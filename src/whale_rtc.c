#include "pcf8523_rp2040.h"
#include "whale_rtc.h"

int w_rtc_init(void) {

	//i2c init
	i2c_init(W_RTC_I2C, 500 * 1000);
	uint i2c_index = I2C_NUM(W_RTC_I2C);
	gpio_set_function(W_RTC_SCL, GPIO_FUNC_I2C);
	gpio_set_function(W_RTC_SDA, GPIO_FUNC_I2C);

	//gpio pulls
	gpio_pull_up(W_RTC_SCL);	
	gpio_pull_up(W_RTC_SDA);

	//set caps
	if(!pcf8523_cap_sel_set(i2c_index, CAP_SEL_7_PF)) return RTC_ERR;

	//ensure time is running
	if(!pcf8523_time_circuit_start(i2c_index)) return RTC_ERR;

	//enable bat switchover
	if(!pcf8523_pm_function_set(i2c_index, 0x0)) return RTC_ERR;

	//set 24h mode
	if(!pcf8523_hour_mode_set(i2c_index, HOUR_MODE_24)) return RTC_ERR;


	return RTC_OK;
}



int w_rtc_datetime_get(struct w_rtc_datetime_t *_datetime) {

	uint i2c_index = I2C_NUM(W_RTC_I2C);
	//pull the registers
	pcf8523_seconds_get(i2c_index, &_datetime->seconds);
	pcf8523_minutes_get(i2c_index, &_datetime->minutes);
	pcf8523_hours_get(i2c_index, &_datetime->hours);
	pcf8523_days_get(i2c_index, &_datetime->days);
	pcf8523_months_get(i2c_index, &_datetime->months);
	pcf8523_years_get(i2c_index, &_datetime->years);
	
	return RTC_OK;
}
