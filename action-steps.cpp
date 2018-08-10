#include <Arduino.h>

#include "test-steps.h"
#include "test-runner.h"

void ask_user_to_start_test(int param) {
	(void)param;
	test_runner_write_lcd_P(
		PSTR("  ASAP Watercrafts  "),
		PSTR("   User PCB Tests   "),
		PSTR("  Press OK to start "),
		NULL
	);
}

void ask_user_to_remove_keyfob(int param)
{
	(void)param;
	test_runner_write_lcd_P(
		NULL,
		PSTR("       Remove       "),
		PSTR("       Keyfob       "),
		NULL
	);
}
void ask_user_to_turn_power_off(int param) { (void)param; }
void ask_user_to_turn_power_on(int param) { (void)param; }
void ask_user_to_confirm_intro(int param) { (void)param; }
void ask_user_to_confirm_no_leds(int param) { (void)param; }
void ask_user_to_confirm_heatbeat_led(int param) { (void)param; }
void ask_user_to_watch_battery_leds(int param) { (void)param; }
void ask_user_to_insert_keyfob(int param) { (void)param; }
void ask_user_to_place_keyfob(int param) { (void)param; }
void ask_user_to_confirm_batt_led_seq(int param) { (void)param; }
void ask_user_to_confirm_batt_led_flash(int param) { (void)param; }
void ask_user_to_confirm_batt_led_count(int param) { (void)param; }
void ask_user_to_confirm_speed_led_count(int param) { (void)param; }
void ask_user_to_confirm_flood_warning(int param) { (void)param; }

void turn_power_on(int param) { (void)param; }
void turn_battery_on(int param) { (void)param; }
void turn_charger_on(int param) { (void)param; }

void turn_power_off(int param) { (void)param; }
void turn_battery_off(int param) { (void)param; }
void turn_charger_off(int param) { (void)param; }

void set_throttles(int param) { (void)param; }
void set_power_supply_to_volts(int param) { (void)param; }
void set_speed_pwm(int param) { (void)param; }
void set_flood_sensor(int param) { (void)param; }

void delay_for_ms(int param)
{
	delay(param);
}
