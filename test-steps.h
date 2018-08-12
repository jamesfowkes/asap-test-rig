#ifndef _TEST_STEPS_H_
#define _TEST_STEPS_H_

struct test_result
{
	bool test_complete;
	bool pass;
};
typedef struct test_result TEST_RESULT;

typedef void (*ACTION_FN)(int param);
typedef void (*TEST_FN)(TEST_RESULT& test_result);

struct test_step
{
	ACTION_FN action_fn;
	uint16_t param;
	TEST_FN test_fn;
};
typedef struct test_step TEST_STEP;

/* These functions take actions. They are called via the s_test_steps array in test-sequence.cpp */

void control_internal_power(int param);
void control_battery(int param);
void control_charger(int param);

void print_powering_board(int param);
void signal_standby(int param);

void ask_user_to_start_test(int param);
void ask_user_to_remove_keyfob(int param);
void ask_user_to_confirm_intro(int param);
void ask_user_to_confirm_no_leds(int param);
void ask_user_to_confirm_heatbeat_led(int param);
void ask_user_to_watch_battery_leds(int param);
void ask_user_to_insert_keyfob(int param);
void ask_user_to_confirm_batt_led_seq(int param);
void ask_user_to_confirm_batt_led_flash(int param);
void ask_user_to_confirm_batt_led_count(int param);
void ask_user_to_confirm_speed_led_count(int param);
void ask_user_to_confirm_flood_warning(int param);
void ask_user_to_confirm_charging(int param);

void set_throttles(int param);
void set_power_supply_to_volts(int param);
void set_power_supply_to_volts_direct(int param);
void set_battery_to_volts(int param);
void set_speed_pwm(int param);
void set_molex_flood_sensor(int param);
void set_din_flood_sensor(int param);
void safe_powerdown(int param);

/* After test actions, these functions test the state of the system. These are the actual pass/fail functions. */

void check_user_input(TEST_RESULT& result);
void keyfob_removed(TEST_RESULT& result);
void check_power_control_on(TEST_RESULT& result);
void check_power_control_off(TEST_RESULT& result);
void check_high_voltage_supply(TEST_RESULT& result);

#endif
