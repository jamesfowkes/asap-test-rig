/*
 * C/C++/Arduino Includes
 */

#include <Arduino.h>

#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>
#include <TaskAction.h>

/*
 * ADL Includes
 */

#include "device.h"
#include "parameter.h"
#include "adl.h"

#include "sparkfun-serial-lcd.h"
#include "debounced-input.h"
#include "digital-input.h"
#include "digital-output.h"
#include "adafruit-mcp4725.h"
#include "adafruit-ads1x15.h"

/*
 * Local Includes
 */

#include "test-steps.h"
#include "test-runner.h"
#include "test-devices.h"

#include "util.h"

/*
 * Defines, typedefs, constants
 */

static const char TWENTY_SPACES[] = "                    ";

/*
 * Local Variables
 */

static char s_local_line_buffer[21];

/*
 * Public Functions
 */

char * lcd_get_test_number_line()
{
    sprintf(s_local_line_buffer, "Test step %d:", test_sequencer_get_current_test_number()+1);
    fill_with_spaces(s_local_line_buffer, 20);
    return s_local_line_buffer;
}

void lcd_write_line(const char * fmt, ...)
{
    if (fmt)
    {
        va_list args;
        va_start (args, fmt); vsnprintf(s_local_line_buffer, 21, fmt, args); va_end (args);
        fill_with_spaces(s_local_line_buffer, 20);
        get_dev_lcd()->print(s_local_line_buffer);
    }
    else
    {
        get_dev_lcd()->print(TWENTY_SPACES);    
    }
}

void lcd_write_line_P(const char * line)
{
    if (line)
    {
        strcpy_P(s_local_line_buffer, line);
        fill_with_spaces(s_local_line_buffer, 20);
        get_dev_lcd()->print(s_local_line_buffer);
    }
    else
    {
        get_dev_lcd()->print(TWENTY_SPACES);    
    }   
}

void lcd_write(const char * line1, const char * line2, const char * line3, const char * line4)
{
    get_dev_lcd()->clear();
    lcd_write_line(line1);
    lcd_write_line(line2);
    lcd_write_line(line3);
    lcd_write_line(line4);
}

void lcd_write_P(const char * line1, const char * line2, const char * line3, const char * line4)
{
    get_dev_lcd()->clear();
    lcd_write_line_P(line1);
    lcd_write_line_P(line2);
    lcd_write_line_P(line3);
    lcd_write_line_P(line4);
}