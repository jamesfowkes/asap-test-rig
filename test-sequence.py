TEST_STEPS = [
    ("ask_user_to_start_test", 0, "check_user_input"),
    ("ask_user_to_remove_keyfob", 1, "check_user_input"),
    ("print_powering_board", 0, "continue_immediately"),
    None,

    ("control_internal_power", 1, "continue_immediately"),
    ("delay_for_ms",750, "delay_expired"),
    ("set_power_supply_to_volts_direct",560, "check_high_voltage_supply"),
    ("control_battery",1, "continue_immediately"),
    ("delay_for_ms",2000, "delay_expired"),
    None,

    (None, 0, "check_power_control_off"),
    ("Ask user to confirm intro", 0, "check_user_input"),
    ("Ask user to confirm no leds", 0, "check_user_input"),
    ("Ask user to confirm heatbeat led", 0, "check_user_input"),
    ("Ask user to insert keyfob", 0, "check_user_input"),
    ("Signal standby", 0, "continue_immediately"),
    ("delay_for_ms",2000, "delay_expired"),
    (None, 0, "check_power_control_on"),
    ("Ask user to confirm intro", 0, "check_user_input"),
    ("Ask user to confirm batt led count", 8, "check_user_input"),
    ("Ask user to confirm speed led count", 0, "check_user_input"),
    None,

    ("Set throttles", 1, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Ask user to confirm speed led count", 0, "check_user_input"),
    None,

    ("Set throttles", 2, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Ask user to confirm speed led count", 0, "check_user_input"),
    None,

    ("Set throttles", 3, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Ask user to confirm speed led count", 0, "check_user_input"),
    None,

    ("Set throttles", 0, "continue_immediately"),
    None,

    ("Ask user to watch battery leds", 0, "check_user_input"),
    ("Set battery to volts", 518, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Set battery to volts", 492, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Set battery to volts", 475, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Set battery to volts", 460, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Set battery to volts", 449, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Set battery to volts", 438, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Set battery to volts", 430, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Set battery to volts", 421, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    None,
    ("Ask user to confirm batt led seq", 0, "check_user_input"),
    ("Ask user to confirm batt led flash", 0, "check_user_input"),
    None,
    ("Set throttles", 1, "continue_immediately"),
    ("Set speed pwm", 25, "continue_immediately"),
    ("Ask user to confirm speed led count", 1, "check_user_input"),
    None,
    ("Set throttles", 2, "continue_immediately"),
    ("Set speed pwm", 50, "continue_immediately"),
    ("Ask user to confirm speed led count", 2, "check_user_input"),
    None,

    ("Set throttles", 3, "continue_immediately"),
    ("Set speed pwm", 75, "continue_immediately"),
    ("Ask user to confirm speed led count", 3, "check_user_input"),
    None,

    ("Set throttles", 3, "continue_immediately"),
    ("Set speed pwm", 105, "continue_immediately"),
    ("Ask user to confirm speed led count", 4, "check_user_input"),
    ("Set throttles", 0, "continue_immediately"),
    ("Set speed pwm", 0, "continue_immediately"),
    None,

    ("Set molex flood sensor", 1, "continue_immediately"),
    ("Ask user to confirm flood warning", 1, "check_user_input"),
    (None, 0, "check_power_control_off"),
    None,

    ("Set molex flood sensor", 0, "continue_immediately"),
    ("Ask user to confirm flood warning", 0, "check_user_input"),
    (None, 0, "check_power_control_on"),
    None,

    ("Set DIN flood sensor", 1, "continue_immediately"),
    ("Ask user to confirm flood warning", 1, "check_user_input"),
    (None, 0, "check_power_control_off"),
    None,

    ("Set DIN flood sensor", 0, "continue_immediately"),
    ("Ask user to confirm flood warning", 0, "check_user_input"),
    (None, 0, "check_power_control_on"),
    None,

    ("Ask user to remove keyfob", 0, "check_user_input"),
    (None, 0, "check_power_control_off"),
    ("Ask user to confirm batt led count", 0, "check_user_input"),
    None,

    ("Set molex flood sensor", 1, "continue_immediately"),
    ("Ask user to confirm flood warning", 1, "check_user_input"),
    (None, 0, "check_power_control_off"),
    ("Set molex flood sensor", 0, "continue_immediately"),

    ("Set DIN flood sensor", 1, "continue_immediately"),
    ("Ask user to confirm flood warning", 1, "check_user_input"),
    (None, 0, "check_power_control_off"),
    ("Set DIN flood sensor", 0, "continue_immediately"),
    None,

    ("Set battery to volts", 500, "continue_immediately"),
    ("Signal standby", 0, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
    ("Control charger", 1, "continue_immediately"),
    ("Ask user to confirm charging", 1, "check_user_input"),
    ("Control charger", 0, "continue_immediately"),
    ("Ask user to confirm charging", 0, "check_user_input"),
    None,

    ("Signal standby", 0, "continue_immediately"),
    ("Safe powerdown", 0, "continue_immediately"),
    ("Delay for ms", 1000, "delay_expired"),
]

if __name__ == "__main__":

    longest_action_string = max([len(s[0]) for s in TEST_STEPS if s and s[0]])
    longest_test_string = max([len(s[2]) for s in TEST_STEPS if s])

    test_count = 0  
    for s in TEST_STEPS:
        if s:
            test_count += 1
            action_function = s[0].lower().replace(" ", "_") if s[0] else "NULL"
            action_function = "{:{width}}".format(action_function+",", width=longest_action_string+2)

            step_param = "{:6}".format(str(s[1]) + ",")
            test_function = "{:{width}}".format(s[2], width=longest_test_string+2)

            struct_data = "".join([action_function, step_param, test_function])
            print("\t{{{}}}, // Test {}".format(struct_data, test_count))
        else:
            print("")
