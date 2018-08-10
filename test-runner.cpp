#include <Arduino.h>

#include "device.h"
#include "parameter.h"
#include "adl.h"

#include "sparkfun-serial-lcd.h"
#include "debounced-input.h"

#include "test-runner.h"

static DebouncedInput * sp_button;
static SparkfunSerialLCD * sp_lcd;

static char s_current_test[20];

static void lcd_write_line_P(const char * line)
{
	char lcd_buffer[21] = "                    ";
	if (line)
	{
		strcpy_P(lcd_buffer, line);
	}
	sp_lcd->print(lcd_buffer);
}

void end_test(bool success)
{
	if (success)
	{
		test_runner_write_lcd_P(NULL, PSTR("   TEST COMPLETE!   "), PSTR("  All tests passed! "), NULL);
	}
	else
	{
		test_runner_write_lcd_P(PSTR("   TESTS FAILED!    "), PSTR("Failed at test:"), s_current_test, NULL);
	}

}

void adl_custom_setup(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
	(void)ndevices; (void)pparams; (void)nparams;
	sp_button = (DebouncedInput*)pdevices[0];
	sp_lcd = (SparkfunSerialLCD*)pdevices[2];
	
}

void adl_custom_loop(DeviceBase * pdevices[], int ndevices, ParameterBase * pparams[], int nparams)
{
	(void)pdevices; (void)ndevices; (void)pparams; (void)nparams;
	test_sequencer_run();
}

void test_runner_write_lcd(char * line1, char * line2, char * line3, char * line4)
{
	sp_lcd->clear();
	sp_lcd->print(line1);
	sp_lcd->print(line2);
	sp_lcd->print(line3);
	sp_lcd->print(line4);
}

void test_runner_write_lcd_P(const char * line1, const char * line2, const char * line3, const char * line4)
{
	sp_lcd->clear();
	lcd_write_line_P(line1);
	lcd_write_line_P(line2);
	lcd_write_line_P(line3);
	lcd_write_line_P(line4);
}

bool test_runner_get_button_state()
{
	Serial.println(sp_button->state());
	return sp_button->check_low_and_clear();
}
