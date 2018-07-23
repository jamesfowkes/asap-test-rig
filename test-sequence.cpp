#include <stdint.h>

#include "test-steps.h"

TEST_STEP s_test_steps[] = {
	{ask_user_to_start_test,				0},
	{ask_user_to_remove_keyfob,				0},
	{ask_user_to_turn_power_off,			0},
	{set_power_supply_to_volts,				530},
	{ask_user_to_turn_power_on,				0},
	{ask_user_to_confirm_intro,				0},
	{ask_user_to_confirm_no_leds,			0},
	{ask_user_to_confirm_heatbeat_led,		0},
	{confirm_power_control_state,			0},
	{ask_user_to_insert_keyfob,				0},
	{ask_user_to_place_keyfob,				0},
	{ask_user_to_confirm_intro,				0},
	{confirm_power_control_state,			1},
	{confirm_battery_leds_state,			8},
	{confirm_speed_leds_state,				0},

	{set_throttles,							1},
	{delay_for_ms,							1000},
	{confirm_speed_leds_state,				0},

	{set_throttles,							2},
	{delay_for_ms,							1000},
	{confirm_speed_leds_state,				0},

	{set_throttles,							3},
	{delay_for_ms,							1000},
	{confirm_speed_leds_state,				0},

	{set_throttles,							0},

	{ask_user_to_watch_battery_leds,		0},
	{set_power_supply_to_volts,				495},
	{delay_for_ms,							1000},
	{set_power_supply_to_volts,				475},
	{delay_for_ms,							1000},
	{set_power_supply_to_volts,				458},
	{delay_for_ms,							1000},
	{set_power_supply_to_volts,				445},
	{delay_for_ms,							1000},
	{set_power_supply_to_volts,				434},
	{delay_for_ms,							1000},
	{set_power_supply_to_volts,				424},
	{delay_for_ms,							1000},
	{set_power_supply_to_volts,				418},
	{delay_for_ms,							1000},
	{set_power_supply_to_volts,				410},
	{delay_for_ms,							1000},

	{ask_user_to_confirm_batt_led_seq,		0},
	{ask_user_to_confirm_batt_led_flash,	0},

	{set_throttles,							1},
	{set_speed_pwm,							25},
	{confirm_speed_leds_state,				1},

	{set_throttles,							2},
	{set_speed_pwm,							50},
	{confirm_speed_leds_state,				2},

	{set_throttles,							3},
	{set_speed_pwm,							75},
	{confirm_speed_leds_state,				3},

	{set_flood_sensor,						1},
	{ask_user_to_confirm_flood_warning,		1},
	{confirm_power_control_state,			0},

	{set_flood_sensor,						0},
	{ask_user_to_confirm_flood_warning,		0},
	{confirm_power_control_state,			1},

	{ask_user_to_remove_keyfob,				0},
	{confirm_power_control_state,			0},
	{confirm_battery_leds_state,			0},

	{set_flood_sensor,						1},
	{ask_user_to_confirm_flood_warning,		1},
	{confirm_power_control_state,			0}
};

static const uint16_t TEST_STEP_COUNT = sizeof(s_test_steps) / sizeof(TEST_STEP);

static uint16_t s_seq_index = 0;

void sequencer_next_step()
{
	if (s_seq_index >= TEST_STEP_COUNT) { return; }

	TEST_STEP * pStep = &s_test_steps[s_seq_index];

	pStep->fn(pStep->param);

	s_seq_index++;
}

