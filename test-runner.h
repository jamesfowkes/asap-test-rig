#ifndef _TEST_RUNNER_H_
#define _TEST_RUNNER_H_

void test_runner_wait_for_user_input();
void test_runner_start_delay(int delay_ms);
void test_runner_write_lcd(char * line1, char * line2, char * line3, char * line4);

void sequencer_next_step();

#endif
