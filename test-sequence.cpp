#include <stdint.h>

#include <TaskAction.h>

#include "log.h"
#include "test-steps.h"
#include "test-runner.h"

static void continue_immediately(TEST_RESULT& result)
{
	result.test_complete = true;
	result.pass = true;
}

static void delay_expired(TEST_RESULT& result)
{
	(void)result;
}

static const TEST_STEP s_test_steps[] = {
	{ask_user_to_start_test,              0,    check_user_input         }, // Test 1
	{ask_user_to_remove_keyfob,           0,    keyfob_removed           }, // Test 2
	{set_power_supply_to_volts,           530,  continue_immediately     }, // Test 3
	{turn_power_on,                       0,    check_power_control_off  }, // Test 4
	{ask_user_to_confirm_intro,           0,    check_user_input         }, // Test 5
	{ask_user_to_confirm_no_leds,         0,    check_user_input         }, // Test 6
	{ask_user_to_confirm_heatbeat_led,    0,    check_user_input         }, // Test 7
	{ask_user_to_insert_keyfob,           0,    check_user_input         }, // Test 8
	{NULL,                                0,    check_power_control_on   }, // Test 9
	{ask_user_to_confirm_intro,           0,    check_user_input         }, // Test 10
	{ask_user_to_confirm_batt_led_count,  8,    check_user_input         }, // Test 11
	{ask_user_to_confirm_speed_led_count, 0,    check_user_input         }, // Test 12
	{set_throttles,                       1,    continue_immediately     }, // Test 13
	{delay_for_ms,                        1000, delay_expired            }, // Test 14
	{ask_user_to_confirm_speed_led_count, 0,    check_user_input         }, // Test 15
	{set_throttles,                       2,    continue_immediately     }, // Test 16
	{delay_for_ms,                        1000, delay_expired            }, // Test 17
	{ask_user_to_confirm_speed_led_count, 0,    check_user_input         }, // Test 18
	{set_throttles,                       3,    continue_immediately     }, // Test 19
	{delay_for_ms,                        1000, delay_expired            }, // Test 20
	{ask_user_to_confirm_speed_led_count, 0,    check_user_input         }, // Test 21
	{set_throttles,                       0,    continue_immediately     }, // Test 22
	{ask_user_to_watch_battery_leds,      0,    check_user_input         }, // Test 23
	{set_power_supply_to_volts,           495,  continue_immediately     }, // Test 24
	{delay_for_ms,                        1000, delay_expired            }, // Test 25
	{set_power_supply_to_volts,           475,  continue_immediately     }, // Test 26
	{delay_for_ms,                        1000, delay_expired            }, // Test 27
	{set_power_supply_to_volts,           458,  continue_immediately     }, // Test 28
	{delay_for_ms,                        1000, delay_expired            }, // Test 29
	{set_power_supply_to_volts,           445,  continue_immediately     }, // Test 30
	{delay_for_ms,                        1000, delay_expired            }, // Test 31
	{set_power_supply_to_volts,           434,  continue_immediately     }, // Test 32
	{delay_for_ms,                        1000, delay_expired            }, // Test 33
	{set_power_supply_to_volts,           424,  continue_immediately     }, // Test 34
	{delay_for_ms,                        1000, delay_expired            }, // Test 35
	{set_power_supply_to_volts,           418,  continue_immediately     }, // Test 36
	{delay_for_ms,                        1000, delay_expired            }, // Test 37
	{set_power_supply_to_volts,           410,  continue_immediately     }, // Test 38
	{delay_for_ms,                        1000, delay_expired            }, // Test 39
	{ask_user_to_confirm_batt_led_seq,    0,    check_user_input         }, // Test 40
	{ask_user_to_confirm_batt_led_flash,  0,    check_user_input         }, // Test 41
	{set_throttles,                       1,    continue_immediately     }, // Test 42
	{set_speed_pwm,                       25,   continue_immediately     }, // Test 43
	{ask_user_to_confirm_speed_led_count, 1,    check_user_input         }, // Test 44
	{set_throttles,                       2,    continue_immediately     }, // Test 45
	{set_speed_pwm,                       50,   continue_immediately     }, // Test 46
	{ask_user_to_confirm_speed_led_count, 2,    check_user_input         }, // Test 47
	{set_throttles,                       3,    continue_immediately     }, // Test 48
	{set_speed_pwm,                       75,   continue_immediately     }, // Test 49
	{ask_user_to_confirm_speed_led_count, 3,    check_user_input         }, // Test 50
	{set_flood_sensor,                    1,    continue_immediately     }, // Test 51
	{ask_user_to_confirm_flood_warning,   1,    check_user_input         }, // Test 52
	{NULL,                                0,    check_power_control_off  }, // Test 53
	{set_flood_sensor,                    0,    continue_immediately     }, // Test 54
	{ask_user_to_confirm_flood_warning,   0,    check_user_input         }, // Test 55
	{NULL,                                0,    check_power_control_on   }, // Test 56
	{ask_user_to_remove_keyfob,           0,    check_user_input         }, // Test 57
	{NULL,                                0,    check_power_control_off  }, // Test 58
	{ask_user_to_confirm_batt_led_count,  0,    check_user_input         }, // Test 59
	{set_flood_sensor,                    1,    continue_immediately     }, // Test 60
	{ask_user_to_confirm_flood_warning,   1,    check_user_input         }, // Test 61
	{NULL,                                0,    check_power_control_off  }, // Test 62
};
static const uint16_t TEST_STEP_COUNT = sizeof(s_test_steps) / sizeof(TEST_STEP);

static const int16_t WAITING_TO_START = -1;
static int16_t s_seq_index = WAITING_TO_START;

static TEST_RESULT s_last_test_result;

static void test_sequencer_run_current_action_step()
{
	if (s_seq_index < TEST_STEP_COUNT)
	{
		TEST_STEP const * const pStep = &s_test_steps[s_seq_index];

		p("Running test step %d...", s_seq_index+1);

		if(pStep->action_fn)
		{
			s_last_test_result.test_complete = false;
			s_last_test_result.pass = false;
			pStep->action_fn(pStep->param);
		}
	}
	else
	{
		end_test(true);
	}
}

static void test_sequencer_task_fn(TaskAction * task)
{
	(void)task;
	TEST_STEP const * const pStep = &s_test_steps[s_seq_index];

	pStep->test_fn(s_last_test_result);

	if (s_last_test_result.test_complete)
	{
		if (s_last_test_result.pass)
		{
			pln("passed!");
			s_seq_index++;
			test_sequencer_run_current_action_step();
		}
		else
		{
			pln("failed!");
			end_test(false);
		}
	}
}
static TaskAction s_test_sequencer_task(test_sequencer_task_fn, 100, INFINITE_TICKS);

void test_sequencer_run()
{
	if (s_seq_index == WAITING_TO_START)
	{
		s_seq_index	= 0;
		test_sequencer_run_current_action_step();
	}

	if (s_seq_index < TEST_STEP_COUNT)
	{
		s_test_sequencer_task.tick();
	}
}
