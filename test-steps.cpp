#include <stdint.h>

#include "test-steps.h"
#include "test-runner.h"

void check_user_input(TEST_RESULT& result)
{
	if (test_runner_get_button_state())
	{
		result.test_complete = true;
		result.pass = true;
	}
}

void keyfob_removed(TEST_RESULT& result) { (void)result;}

void check_power_control_state(TEST_RESULT& result) { (void)result;}

void check_power_control_on(TEST_RESULT& result) { (void)result;}

void check_power_control_off(TEST_RESULT& result) { (void)result;}
