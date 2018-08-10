#ifndef _TEST_RUNNER_H_
#define _TEST_RUNNER_H_

void test_runner_write_lcd(char * line1, char * line2, char * line3, char * line4);
void test_runner_write_lcd_P(const char * line1, const char * line2, const char * line3, const char * line4);

bool test_runner_get_button_state();

void test_sequencer_run();

void end_test(bool success);

#endif
