#include <Arduino.h>

#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

#include <TaskAction.h>

#include "device.h"
#include "parameter.h"
#include "adl.h"

#include "sparkfun-serial-lcd.h"
#include "debounced-input.h"
#include "digital-input.h"
#include "digital-output.h"
#include "adafruit-mcp4725.h"
#include "adafruit-ads1x15.h"

#include "test-steps.h"
#include "test-runner.h"
#include "test-devices.h"

#include "log.h"

typedef enum _ads_channel
{
	ADS_CHANNEL_LOCAL_HI_VOLT,
	ADS_CHANNEL_POWER_CONTROL,
	ADS_CHANNEL_CHARGE,
	ADS_CHANNEL_5V
} ADS_CHANNEL;

void check_user_input(TEST_RESULT& result)
{
	if (get_dev_ok_button()->check_low_and_clear())
	{
		result.test_complete = true;
		result.pass = true;
	}
}

void keyfob_removed(TEST_RESULT& result) { (void)result;}

void check_power_control_state(TEST_RESULT& result) { (void)result;}

void check_power_control_on(TEST_RESULT& result)
{
	unsigned long hi_volt_reading = get_dev_high_voltage_adc()->get_reading(ADS_CHANNEL_LOCAL_HI_VOLT, ADS_READING_SCALED);
	unsigned long power_control_reading = get_dev_high_voltage_adc()->get_reading(ADS_CHANNEL_POWER_CONTROL, ADS_READING_SCALED);
	unsigned long diff = max(hi_volt_reading, power_control_reading) - min(hi_volt_reading, power_control_reading);
	pln_P(PSTR("\tGot high voltage read %umv"), (uint16_t)hi_volt_reading);
	pln_P(PSTR("\tGot power control voltage read %umv"), (uint16_t)power_control_reading);
	result.test_complete = true;
	result.pass = diff <= 1000;
}

void check_power_control_off(TEST_RESULT& result)
{
	unsigned long power_control_reading = get_dev_high_voltage_adc()->get_reading(ADS_CHANNEL_POWER_CONTROL, ADS_READING_SCALED);
	pln_P(PSTR("\tGot power control voltage read %umv"), (uint16_t)power_control_reading);
	result.test_complete = true;
	result.pass = power_control_reading <= 1000;
}


void check_high_voltage_supply(TEST_RESULT& result)
{
	unsigned long reading = get_dev_high_voltage_adc()->get_reading(ADS_CHANNEL_LOCAL_HI_VOLT, ADS_READING_SCALED);
	pln_P(PSTR("\tGot high voltage read %umv"), (uint16_t)reading);
	result.test_complete = true;
	result.pass = ((reading >= 41300) and (reading <= 61900));
}
