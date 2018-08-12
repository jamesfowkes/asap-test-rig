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
#include "speed-output.h"

#include "util.h"

#include "log.h"

/*
 * Defines, typedefs, constants
 */

/*
 * Local Variables
 */

static uint8_t s_setting;
static unsigned long s_turn_off_time = 0;

/*
 * Private Functions
 */

static void speed_output_task_fn(TaskAction * task)
{
	(void)task;
	if (s_setting > 0)
	{
		get_dev_speed_signal()->set(true);
		s_turn_off_time = millis() + s_setting;
	}
}
static TaskAction s_speed_output_task(speed_output_task_fn, 100, INFINITE_TICKS);

/*
 * Public Functions
 */

void speed_output_run()
{
	s_speed_output_task.tick();
	if (millis() >= s_turn_off_time)
	{
		get_dev_speed_signal()->set(false);
	}
}

void speed_output_set(uint8_t setting)
{
	if (setting <= 105)
	{
		pln_P(PSTR("\tSetting speed to %u%%"), setting);
		s_setting = setting;
	}
}
