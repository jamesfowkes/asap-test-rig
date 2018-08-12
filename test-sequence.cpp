#include <Arduino.h>

#include <TaskAction.h>

#include "test-steps.h"
#include "test-runner.h"

#include "log.h"

static unsigned long s_delay_end = 0;

static void continue_immediately(TEST_RESULT& result)
{
    result.test_complete = true;
    result.pass = true;
}

static void delay_for_ms(int param)
{
    pln_P(PSTR("\tStarting %dms delay..."), param);
    s_delay_end = millis() + param; 
}


static void delay_expired(TEST_RESULT& result)
{
    if (millis() >= s_delay_end)
    {
        result.test_complete = true;
        result.pass = true;
    }
}

static const PROGMEM TEST_STEP s_test_steps[] = {
    {ask_user_to_start_test,              0,    check_user_input           }, // Test 1
    {ask_user_to_remove_keyfob,           1,    check_user_input           }, // Test 2
    {print_powering_board,                0,    continue_immediately       }, // Test 3

    {control_internal_power,              1,    continue_immediately       }, // Test 4
    {delay_for_ms,                        750,  delay_expired              }, // Test 5
    {set_power_supply_to_volts_direct,    560,  check_high_voltage_supply  }, // Test 6
    {control_battery,                     1,    continue_immediately       }, // Test 7
    {delay_for_ms,                        2000, delay_expired              }, // Test 8

    {NULL,                                0,    check_power_control_off    }, // Test 9
    {ask_user_to_confirm_intro,           0,    check_user_input           }, // Test 10
    {ask_user_to_confirm_no_leds,         0,    check_user_input           }, // Test 11
    {ask_user_to_confirm_heatbeat_led,    0,    check_user_input           }, // Test 12
    {ask_user_to_insert_keyfob,           0,    check_user_input           }, // Test 13
    {signal_standby,                      0,    continue_immediately       }, // Test 14
    {delay_for_ms,                        2000, delay_expired              }, // Test 15
    {NULL,                                0,    check_power_control_on     }, // Test 16
    {ask_user_to_confirm_intro,           0,    check_user_input           }, // Test 17
    {ask_user_to_confirm_batt_led_count,  8,    check_user_input           }, // Test 18
    {ask_user_to_confirm_speed_led_count, 0,    check_user_input           }, // Test 19

    {set_throttles,                       1,    continue_immediately       }, // Test 20
    {delay_for_ms,                        1000, delay_expired              }, // Test 21
    {ask_user_to_confirm_speed_led_count, 0,    check_user_input           }, // Test 22

    {set_throttles,                       2,    continue_immediately       }, // Test 23
    {delay_for_ms,                        1000, delay_expired              }, // Test 24
    {ask_user_to_confirm_speed_led_count, 0,    check_user_input           }, // Test 25

    {set_throttles,                       3,    continue_immediately       }, // Test 26
    {delay_for_ms,                        1000, delay_expired              }, // Test 27
    {ask_user_to_confirm_speed_led_count, 0,    check_user_input           }, // Test 28

    {set_throttles,                       0,    continue_immediately       }, // Test 29

    {ask_user_to_watch_battery_leds,      0,    check_user_input           }, // Test 30
    {set_battery_to_volts,                518,  continue_immediately       }, // Test 31
    {delay_for_ms,                        1000, delay_expired              }, // Test 32
    {set_battery_to_volts,                492,  continue_immediately       }, // Test 33
    {delay_for_ms,                        1000, delay_expired              }, // Test 34
    {set_battery_to_volts,                475,  continue_immediately       }, // Test 35
    {delay_for_ms,                        1000, delay_expired              }, // Test 36
    {set_battery_to_volts,                460,  continue_immediately       }, // Test 37
    {delay_for_ms,                        1000, delay_expired              }, // Test 38
    {set_battery_to_volts,                449,  continue_immediately       }, // Test 39
    {delay_for_ms,                        1000, delay_expired              }, // Test 40
    {set_battery_to_volts,                438,  continue_immediately       }, // Test 41
    {delay_for_ms,                        1000, delay_expired              }, // Test 42
    {set_battery_to_volts,                430,  continue_immediately       }, // Test 43
    {delay_for_ms,                        1000, delay_expired              }, // Test 44
    {set_battery_to_volts,                421,  continue_immediately       }, // Test 45
    {delay_for_ms,                        1000, delay_expired              }, // Test 46

    {ask_user_to_confirm_batt_led_seq,    0,    check_user_input           }, // Test 47
    {ask_user_to_confirm_batt_led_flash,  0,    check_user_input           }, // Test 48

    {set_throttles,                       1,    continue_immediately       }, // Test 49
    {set_speed_pwm,                       25,   continue_immediately       }, // Test 50
    {ask_user_to_confirm_speed_led_count, 1,    check_user_input           }, // Test 51

    {set_throttles,                       2,    continue_immediately       }, // Test 52
    {set_speed_pwm,                       50,   continue_immediately       }, // Test 53
    {ask_user_to_confirm_speed_led_count, 2,    check_user_input           }, // Test 54

    {set_throttles,                       3,    continue_immediately       }, // Test 55
    {set_speed_pwm,                       75,   continue_immediately       }, // Test 56
    {ask_user_to_confirm_speed_led_count, 3,    check_user_input           }, // Test 57

    {set_throttles,                       3,    continue_immediately       }, // Test 58
    {set_speed_pwm,                       105,  continue_immediately       }, // Test 59
    {ask_user_to_confirm_speed_led_count, 4,    check_user_input           }, // Test 60
    {set_throttles,                       0,    continue_immediately       }, // Test 61
    {set_speed_pwm,                       0,    continue_immediately       }, // Test 62

    {set_molex_flood_sensor,              1,    continue_immediately       }, // Test 63
    {ask_user_to_confirm_flood_warning,   1,    check_user_input           }, // Test 64
    {NULL,                                0,    check_power_control_off    }, // Test 65

    {set_molex_flood_sensor,              0,    continue_immediately       }, // Test 66
    {ask_user_to_confirm_flood_warning,   0,    check_user_input           }, // Test 67
    {NULL,                                0,    check_power_control_on     }, // Test 68

    {set_din_flood_sensor,                1,    continue_immediately       }, // Test 69
    {ask_user_to_confirm_flood_warning,   1,    check_user_input           }, // Test 70
    {NULL,                                0,    check_power_control_off    }, // Test 71

    {set_din_flood_sensor,                0,    continue_immediately       }, // Test 72
    {ask_user_to_confirm_flood_warning,   0,    check_user_input           }, // Test 73
    {NULL,                                0,    check_power_control_on     }, // Test 74

    {ask_user_to_remove_keyfob,           0,    check_user_input           }, // Test 75
    {NULL,                                0,    check_power_control_off    }, // Test 76
    {ask_user_to_confirm_batt_led_count,  0,    check_user_input           }, // Test 77

    {set_molex_flood_sensor,              1,    continue_immediately       }, // Test 78
    {ask_user_to_confirm_flood_warning,   1,    check_user_input           }, // Test 79
    {NULL,                                0,    check_power_control_off    }, // Test 80
    {set_molex_flood_sensor,              0,    continue_immediately       }, // Test 81
    {set_din_flood_sensor,                1,    continue_immediately       }, // Test 82
    {ask_user_to_confirm_flood_warning,   1,    check_user_input           }, // Test 83
    {NULL,                                0,    check_power_control_off    }, // Test 84
    {set_din_flood_sensor,                0,    continue_immediately       }, // Test 85

    {set_battery_to_volts,                500,  continue_immediately       }, // Test 86
    {signal_standby,                      0,    continue_immediately       }, // Test 87
    {delay_for_ms,                        1000, delay_expired              }, // Test 88
    {control_charger,                     1,    continue_immediately       }, // Test 89
    {ask_user_to_confirm_charging,        1,    check_user_input           }, // Test 90
    {control_charger,                     0,    continue_immediately       }, // Test 91
    {ask_user_to_confirm_charging,        0,    check_user_input           }, // Test 92

    {signal_standby,                      0,    continue_immediately       }, // Test 93
    {safe_powerdown,                      0,    continue_immediately       }, // Test 94
    {delay_for_ms,                        1000, delay_expired              }, // Test 95
};
static const uint16_t TEST_STEP_COUNT = sizeof(s_test_steps) / sizeof(TEST_STEP);

static uint16_t s_seq_index = 0;

static TEST_RESULT s_last_test_result;
static TEST_STEP s_current_test_step;

typedef enum _SEQUENCER_STATE
{
    SEQUENCER_STATE_IDLE,
    SEQUENCER_STATE_ACTION,
    SEQUENCER_STATE_TESTING,
    SEQUENCER_STATE_COMPLETE
} SEQUENCER_STATE;

static SEQUENCER_STATE s_state = SEQUENCER_STATE_IDLE;

static bool all_tests_passed()
{
    return s_seq_index == TEST_STEP_COUNT;
}

static void read_test_step_from_progmem(TEST_STEP& step, int16_t step_number)
{
    memcpy_P(&step, &s_test_steps[step_number], sizeof(TEST_STEP));
}

static void test_sequencer_run_current_action_step()
{
    if (s_seq_index < TEST_STEP_COUNT)
    {
        if(s_current_test_step.action_fn)
        {
            s_last_test_result.test_complete = false;
            s_last_test_result.pass = false;
            s_current_test_step.action_fn(s_current_test_step.param);
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
    switch (s_state)
    {
    case SEQUENCER_STATE_IDLE:
        pln("Starting test sequence");
        read_test_step_from_progmem(s_current_test_step, s_seq_index);
        s_state = SEQUENCER_STATE_ACTION;
        break;
    case SEQUENCER_STATE_ACTION:
        pln("Running test step %d:", s_seq_index+1);
        test_sequencer_run_current_action_step();
        s_state = SEQUENCER_STATE_TESTING;
        break;
    case SEQUENCER_STATE_TESTING:
        s_current_test_step.test_fn(s_last_test_result);
        if (s_last_test_result.test_complete)
        {
            p("Test step %d ", s_seq_index+1);
            if (s_last_test_result.pass)
            {    
                pln("passed!");
                s_seq_index++;
                if (all_tests_passed())
                {
                    pln_P(PSTR("***All tests passed!***"));
                    end_test(true);
                    s_state = SEQUENCER_STATE_COMPLETE;
                }
                else
                {
                    read_test_step_from_progmem(s_current_test_step, s_seq_index);
                    s_state = SEQUENCER_STATE_ACTION;
                }
            }
            else
            {
                pln("failed!");
                end_test(false);
                s_state = SEQUENCER_STATE_COMPLETE;
            }
        }
        break;
    case SEQUENCER_STATE_COMPLETE:
        s_last_test_result.test_complete = false;
        s_last_test_result.pass = false;
        check_user_input(s_last_test_result);
        if (s_last_test_result.pass)
        {
            test_runner_reset_devices();
            s_seq_index = 0;
            s_state = SEQUENCER_STATE_IDLE;
        }
        break;
    }
}
static TaskAction s_test_sequencer_task(test_sequencer_task_fn, 100, INFINITE_TICKS);

void test_sequencer_run()
{
    s_test_sequencer_task.tick();
}

uint8_t test_sequencer_get_current_test_number()
{
    return s_seq_index;
}
