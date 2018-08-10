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

void turn_power_on(int param);
void turn_battery_on(int param);
void turn_charger_on(int param);

void turn_power_off(int param);
void turn_battery_off(int param);
void turn_charger_off(int param);

void ask_user_to_start_test(int param);
void ask_user_to_remove_keyfob(int param);
void ask_user_to_turn_power_off(int param);
void ask_user_to_turn_power_on(int param);
void ask_user_to_confirm_intro(int param);
void ask_user_to_confirm_no_leds(int param);
void ask_user_to_confirm_heatbeat_led(int param);
void ask_user_to_watch_battery_leds(int param);
void ask_user_to_insert_keyfob(int param);
void ask_user_to_place_keyfob(int param);
void ask_user_to_confirm_batt_led_seq(int param);
void ask_user_to_confirm_batt_led_flash(int param);
void ask_user_to_confirm_batt_led_count(int param);
void ask_user_to_confirm_speed_led_count(int param);
void ask_user_to_confirm_flood_warning(int param);

void set_throttles(int param);
void set_power_supply_to_volts(int param);
void set_speed_pwm(int param);
void set_flood_sensor(int param);

void delay_for_ms(int param);

/* After test actions, these functions test the state of the system. These are the actual pass/fail functions. */

void check_user_input(TEST_RESULT& result);
void keyfob_removed(TEST_RESULT& result);
void check_power_control_on(TEST_RESULT& result);
void check_power_control_off(TEST_RESULT& result);

#endif
