#ifndef _TEST_DEVICES_H_
#define _TEST_DEVICES_H_

DebouncedInput  * get_dev_ok_button();
DigitalOutput  * get_dev_din_flood_sense();
SparkfunSerialLCD  * get_dev_lcd();
DigitalOutput  * get_dev_molex_left_throttle();
DigitalOutput  * get_dev_molex_right_throttle();
DigitalOutput  * get_dev_molex_flood_sense();
DigitalOutput  * get_dev_speed_signal();
DigitalInput  * get_dev_din_left_throttle();
DigitalInput  * get_dev_din_right_throttle();
Adafruit_MCP4725ADL  * get_dev_voltage_control_dac();
Adafruit_ADS1x15  * get_dev_high_voltage_adc();
DigitalOutput  * get_dev_high_voltage_supply_relay();
DigitalOutput  * get_dev_charge_relay();
DigitalOutput  * get_dev_battery_supply_relay();

#endif

