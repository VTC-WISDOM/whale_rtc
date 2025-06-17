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
	if(!pcf8523_bso_int_enable(i2c_index)) return RTC_ERR;

	//set 24h mode
	if(!pcf8523_hour_mode_set(i2c_index, HOUR_MODE_24)) return RTC_ERR;


	return RTC_OK;
}



int w_rtc_datetime_get(struct w_rtc_datetime_t *_datetime) {

	uint i2c_index = I2C_NUM(W_RTC_I2C);
	//pull the registers
	uint8_t _dst[7] = {0};
	if(!pcf8523_time_date_reg_get_all(i2c_index, _dst)) return RTC_ERR;

	_datetime->seconds = _dst[0];
	_datetime->minutes = _dst[1];
	_datetime->hours   = _dst[2];
	_datetime->days    = _dst[3];
	//_datetime->weekdays;
	_datetime->months  = _dst[5];
	_datetime->years   = _dst[6];

	return RTC_OK;
}
