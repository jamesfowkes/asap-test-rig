#include <Arduino.h>

#include "device.h"
#include "parameter.h"
#include "adl.h"

#include "sparkfun-serial-lcd.h"

#include "test-runner.h"

enum test_state
{
	TEST_STATE_STARTED,
	TEST_STATE_WAITING_FOR_USER,
	TEST_STATE_WAITING_FOR_DELAY,
	TEST_STATE_FINISHED
};
typedef enum test_state TEST_STATE;

static TEST_STATE s_test_state;
static SparkfunSerialLCD * sp_lcd;
static char s_current_test[20];

static bool user_pressed_ok() { return false; }
static bool user_pressed_not_ok() { return false; }

static bool test_delay_expired() { return false; }

void end_test(bool success)
{
	if (success)
	{
		test_runner_write_lcd("", "   TEST COMPLETE!   ", "  All tests passed! ", "");
	}
	else
	{
		test_runner_write_lcd("   TESTS FAILED!    ", "Failed at test:", s_current_test, "");
	}

}

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
	(void)ndevices; (void)pparams; (void)nparams;
	sp_lcd = (SparkfunSerialLCD*)pdevices[0];
	//DebouncedInput * pButton = (DebouncedInput*)pdevices[0];
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
	switch(s_test_state)
	{
	case TEST_STATE_STARTED:
		sequencer_next_step();
		break;
	case TEST_STATE_WAITING_FOR_USER:
		if (user_pressed_ok())
		{
			sequencer_next_step();
		}
		else if (user_pressed_not_ok())
		{
			end_test(false);
		}
		break;
	case TEST_STATE_WAITING_FOR_DELAY:
		if (test_delay_expired())
		{
			sequencer_next_step();
		}
		break;
	case TEST_STATE_FINISHED:
		break;
	}

}

void test_runner_write_lcd(char * line1, char * line2, char * line3, char * line4)
{
	sp_lcd->clear();
	sp_lcd->print(line1);
	sp_lcd->print(line2);
	sp_lcd->print(line3);
	sp_lcd->print(line4);
}

void test_runner_wait_for_user_input()
{
	s_test_state = TEST_STATE_WAITING_FOR_USER;
}

void test_runner_start_delay(int delay_ms)
{
	s_test_state = TEST_STATE_WAITING_FOR_DELAY;	
}
