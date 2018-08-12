#ifndef _TEST_RUNNER_H_
#define _TEST_RUNNER_H_

bool test_runner_get_button_state();

void test_action_run();

void test_sequencer_run();
uint8_t test_sequencer_get_current_test_number();

void test_runner_reset_devices();
void end_test(bool success);


#endif
