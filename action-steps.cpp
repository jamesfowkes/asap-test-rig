#include <Arduino.h>

#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>
#include <TaskAction.h>

#include "device.h"
#include "parameter.h"
#include "adl.h"

#include "sparkfun-serial-lcd.h"
#include "debounced-input.h"
#include "digital-input.h"
#include "digital-output.h"
#include "adafruit-mcp4725.h"
#include "adafruit-ads1x15.h"

#include "test-steps.h"
#include "test-runner.h"
#include "test-devices.h"
#include "speed-output.h"

#include "lcd.h"

#include "util.h"

#include "log.h"

static const char ON_STR[] PROGMEM = " on";
static const char OFF_STR[] PROGMEM = " off";

static uint16_t s_battery_target = 413;
static uint16_t s_battery_actual = 413;

static int32_t get_mcp_setting_for_voltage(int param)
{
    // 4095 -> 41.3V
    // 2048 -> 61.9V
    static const int32_t MAX_PARAM = 619UL;
    static const int32_t MIN_PARAM = 413UL;
    static const int32_t PARAM_RANGE = MAX_PARAM - MIN_PARAM;

    static const int32_t MAX_SETTING = 4095UL;
    static const int32_t MIN_SETTING = 2048UL;
    static const int32_t SETTING_RANGE = MAX_SETTING - MIN_SETTING;
    
    int32_t inverted_param = MAX_PARAM - param;

    return ((inverted_param * SETTING_RANGE) / PARAM_RANGE) + MIN_SETTING;
}

void ask_user_to_start_test(int param) {
    (void)param;
    pln_P(PSTR("\tAsking for user start..."));
    lcd_write_P(
        PSTR("  ASAP Watercrafts  "),
        PSTR("   User PCB Tests   "),
        PSTR("  Press OK to start "),
        NULL
    );
}

void ask_user_to_remove_keyfob(int param)
{
    (void)param;
    pln_P(PSTR("\tAsking for keyfob remove..."));
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Remove keyfob and  "));
    lcd_write_line_P(PSTR(" and press OK       "));
    lcd_write_line(NULL);
}

void print_powering_board(int param)
{
    (void)param;
    lcd_write_P(
        NULL,
        PSTR(" Powering board...  "),
        NULL,
        NULL
    );
}

void signal_standby(int param)
{
    (void)param;
    lcd_write_P(
        NULL,
        PSTR("     Standby...     "),
        NULL,
        NULL
    );
}

void ask_user_to_confirm_intro(int param)
{
    (void)param;
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Confirm intro LEDs "));
    lcd_write_line_P(PSTR(" played sequence    ")),
    lcd_write_line(NULL);
}

void ask_user_to_confirm_no_leds(int param)
{
    (void)param;
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Confirm no speed or"));
    lcd_write_line_P(PSTR(" or battery LEDs on ")),
    lcd_write_line(NULL);
}

void ask_user_to_confirm_heatbeat_led(int param)
{
    (void)param;
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Confirm heartbeat  "));
    lcd_write_line_P(PSTR(" LED is flashing    ")),
    lcd_write_line(NULL);
}

void ask_user_to_watch_battery_leds(int param)
{
    (void)param;
    pln_P(PSTR("\tAsking to watch battery LEDs..."));
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Watch battery LEDs "));
    lcd_write_line_P(PSTR(" as they extinguish "));
    lcd_write_line_P(PSTR(" press OK to start "));
}

void set_battery_to_volts(int param)
{
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Reducing battery   "));
    lcd_write_line_P(PSTR(" voltage...         "));
    lcd_write_line_P(NULL);
    set_power_supply_to_volts(param);
}
void ask_user_to_insert_keyfob(int param)
{
    (void)param;
    pln_P(PSTR("\tAsking for keyfob insert..."));
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Attach keyfob and  "));
    lcd_write_line_P(PSTR(" and press OK       ")),
    lcd_write_line(NULL);
}

void ask_user_to_confirm_batt_led_seq(int param)
{
    (void)param;
    pln_P(PSTR("\tAsking about battery LEDs..."));
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Did LEDs go off    "));
    lcd_write_line_P(PSTR(" sequentially?      ")),
    lcd_write_line(NULL);
}

void ask_user_to_confirm_batt_led_flash(int param)
{
    (void)param;
    pln_P(PSTR("\tAsking about battery LEDs..."));
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Is last LED        "));
    lcd_write_line_P(PSTR(" flashing?          ")),
    lcd_write_line(NULL);
}

void ask_user_to_confirm_batt_led_count(int param)
{
    pln_P(PSTR("\tAsking for battery LED count..."));
    
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line(" Are there %d battery", param);
    lcd_write_line_P(PSTR(" LEDs lit?          "));
    lcd_write_line(NULL);
}

void ask_user_to_confirm_speed_led_count(int param)
{
    pln_P(PSTR("\tAsking for speed LED count..."));
    
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line(" Are there %d speed", param);
    lcd_write_line_P(PSTR(" LEDs lit?          "));
    lcd_write_line(NULL);
}

void ask_user_to_confirm_flood_warning(int param)
{
    pln_P(PSTR("\tAsking for flood warning check..."));
    
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Is the flood"));
    lcd_write_line(" warning %s?", param ? "ON" : "OFF");
    lcd_write_line(NULL);
}

void ask_user_to_confirm_charging(int param)
{
    pln_P(PSTR("\tAsking for charging check..."));
    
    get_dev_lcd()->clear();
    lcd_write_line(lcd_get_test_number_line());
    lcd_write_line_P(PSTR(" Are LEDS showing   "));
    lcd_write_line("%s charging?", param ? "" : " no");
    lcd_write_line(NULL);
}

void control_internal_power(int param)
{
    p_P(PSTR("\tTurning internal power"));
    pln_P(param ? ON_STR : OFF_STR);
    get_dev_high_voltage_supply_relay()->set((bool)param);
}

void control_battery(int param)
{
    p_P(PSTR("\tTurning battery"));
    pln_P(param ? ON_STR : OFF_STR);
    get_dev_battery_supply_relay()->set(!(bool)param);
}

void control_charger(int param)
{
    p_P(PSTR("\tTurning charger"));
    pln_P(param ? ON_STR : OFF_STR);
    get_dev_charge_relay()->set((bool)param);
}

void set_throttles(int param)
{
    static char const * const THROT_STR[3] = {"LH", "RH", "BOTH"};
    if (param)
    {
        get_dev_lcd()->clear();
        lcd_write_line(lcd_get_test_number_line());
        lcd_write_line(" Testing %s", THROT_STR[param-1]);
        lcd_write_line_P(param < 3 ? PSTR(" throttle"): PSTR(" throttles"));
        lcd_write_line(NULL);
    }

    switch(param)
    {
    case 0:
        get_dev_molex_left_throttle()->tristate();
        get_dev_molex_right_throttle()->tristate();
        break;
    case 1:
        get_dev_molex_left_throttle()->set(false);
        get_dev_molex_right_throttle()->tristate();
        break;
    case 2:
        get_dev_molex_left_throttle()->tristate();
        get_dev_molex_right_throttle()->set(false);
        break;
    case 3:
        get_dev_molex_left_throttle()->set(false);
        get_dev_molex_right_throttle()->set(false);
        break;
    default:
        break;
    }
}

void set_power_supply_to_volts_direct(int param)
{
    s_battery_target = param;
    s_battery_actual = param;
    int32_t setting = get_mcp_setting_for_voltage(s_battery_actual);
    get_dev_voltage_control_dac()->set_voltage(setting, false);
}

void set_power_supply_to_volts(int param)
{
    s_battery_target = param;
}

void set_speed_pwm(int param)
{
    speed_output_set(param);
}

void set_molex_flood_sensor(int param)
{
    get_dev_molex_flood_sense()->set((bool)param);
}

void set_din_flood_sensor(int param)
{
    get_dev_din_flood_sense()->set((bool)param);
}

void safe_powerdown(int param)
{
    (void)param;
    get_dev_din_flood_sense()->set(false);
    get_dev_molex_left_throttle()->tristate();
    get_dev_molex_right_throttle()->tristate();
    get_dev_molex_flood_sense()->set(false);
    get_dev_speed_signal()->set(false);
    get_dev_high_voltage_supply_relay()->set(false);
    get_dev_charge_relay()->set(false);
    get_dev_battery_supply_relay()->set(true);
}

static void test_action_task_fn(TaskAction * task)
{
    (void)task;
    if (s_battery_target != s_battery_actual)
    {
        if (s_battery_target > s_battery_actual)
        {
            s_battery_actual++;
        }
        else
        {
            s_battery_actual--;
        }
        int32_t setting = get_mcp_setting_for_voltage(s_battery_actual);
        get_dev_voltage_control_dac()->set_voltage(setting, false);
    }
}
static TaskAction s_test_action_task(test_action_task_fn, 50, INFINITE_TICKS);

void test_action_run()
{
    s_test_action_task.tick();
    speed_output_run();
}