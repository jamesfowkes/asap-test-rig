#include "test-steps.h"
#include "test-runner.h"

void ask_user_to_start_test(int param) {
	(void)param;
	test_runner_write_lcd(
		"  ASAP Watercrafts  ",
		"   User PCB Tests   ",
		"  Press OK to start ",
		""
	);
}
void ask_user_to_remove_keyfob(int param) {}
void ask_user_to_turn_power_off(int param) {}
void ask_user_to_turn_power_on(int param) {}
void ask_user_to_confirm_intro(int param) {}
void ask_user_to_confirm_no_leds(int param) {}
void ask_user_to_confirm_heatbeat_led(int param) {}
void ask_user_to_watch_battery_leds(int param) {}
void ask_user_to_insert_keyfob(int param) {}
void ask_user_to_place_keyfob(int param) {}
void ask_user_to_confirm_batt_led_seq(int param) {}
void ask_user_to_confirm_batt_led_flash(int param) {}
void ask_user_to_confirm_flood_warning(int param) {}

void set_throttles(int param) {}
void set_power_supply_to_volts(int param) {}
void set_speed_pwm(int param) {}
void set_flood_sensor(int param) {}

void confirm_power_control_state(int param) {}
void confirm_power_control_is_on(int param) {}
void confirm_battery_leds_state(int param) {}
void confirm_speed_leds_state(int param) {}

void delay_for_ms(int param) {}
