#include <Arduino.h>

#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

#include "device.h"
#include "parameter.h"
#include "adl.h"

#include "adl_defs.h"

#include "sparkfun-serial-lcd.h"
#include "debounced-input.h"
#include "digital-input.h"
#include "digital-output.h"
#include "adafruit-mcp4725.h"
#include "adafruit-ads1x15.h"

#include "test-runner.h"
#include "test-devices.h"

#include "lcd.h"

#include "util.h"

static DeviceBase ** sp_devices;

void test_runner_reset_devices()
{
	(void)get_dev_ok_button();
	get_dev_din_flood_sense()->set(false);
	get_dev_lcd()->clear();
	get_dev_molex_left_throttle()->tristate();
	get_dev_molex_right_throttle()->tristate();
	get_dev_molex_flood_sense()->set(false);
	get_dev_speed_signal()->set(false);
	(void)get_dev_din_left_throttle();
	(void)get_dev_din_right_throttle();
	get_dev_voltage_control_dac()->set_voltage(4095, false);
	(void)get_dev_high_voltage_adc();
	get_dev_high_voltage_supply_relay()->set(false);
	get_dev_charge_relay()->set(false);
	get_dev_battery_supply_relay()->set(true);
}

void end_test(bool success)
{
    uint8_t test_number = test_sequencer_get_current_test_number() + 1;

    if (success)
	{
		lcd_write_P(
			PSTR("   TEST COMPLETE!   "),
			PSTR("  All tests passed! "),
			PSTR(" Safe to unplug PCB "),
			PSTR(" Press OK to restart")
		);
	}
	else
	{
		get_dev_lcd()->clear();
		lcd_write_line_P(PSTR("   TESTS FAILED!    "));
		lcd_write_line(" Failed at step %d", test_number);
		lcd_write_line_P(PSTR("    Press OK to     "));
		lcd_write_line_P(PSTR("   restart tests    "));
	}
}

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
	(void)ndevices; (void)pparams; (void)nparams;
	sp_devices = pdevices;
	test_runner_reset_devices();
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
	(void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
	test_sequencer_run();
	test_action_run();
}

DebouncedInput * get_dev_ok_button()
{
	return (DebouncedInput *)sp_devices[0];
}

DigitalOutput * get_dev_din_flood_sense()
{
	return (DigitalOutput *)sp_devices[1];
}

SparkfunSerialLCD * get_dev_lcd()
{
	return (SparkfunSerialLCD *)sp_devices[2];
}

DigitalOutput * get_dev_molex_left_throttle()
{
	return (DigitalOutput *)sp_devices[3];
}

DigitalOutput * get_dev_molex_right_throttle()
{
	return (DigitalOutput *)sp_devices[4];
}

DigitalOutput * get_dev_molex_flood_sense()
{
	return (DigitalOutput *)sp_devices[5];
}

DigitalOutput * get_dev_speed_signal()
{
	return (DigitalOutput *)sp_devices[6];
}

DigitalInput * get_dev_din_left_throttle()
{
	return (DigitalInput *)sp_devices[7];
}

DigitalInput * get_dev_din_right_throttle()
{
	return (DigitalInput *)sp_devices[8];
}

Adafruit_MCP4725ADL * get_dev_voltage_control_dac()
{
	return (Adafruit_MCP4725ADL *)sp_devices[9];
}

Adafruit_ADS1x15 * get_dev_high_voltage_adc()
{
	return (Adafruit_ADS1x15 *)sp_devices[10];
}

DigitalOutput * get_dev_high_voltage_supply_relay()
{
	return (DigitalOutput *)sp_devices[11];
}

DigitalOutput * get_dev_charge_relay()
{
	return (DigitalOutput *)sp_devices[12];
}

DigitalOutput * get_dev_battery_supply_relay()
{
	return (DigitalOutput *)sp_devices[13];
}

