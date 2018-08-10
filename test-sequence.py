TEST_STEPS = [
	("Ask user to start test", 0, "check_user_input"),
	("Ask user to remove keyfob", 0, "keyfob_removed"),
	("Set power supply to volts", 530, "continue_immediately"),
	("Turn power on", 0, "check_power_control_off"),
	("Ask user to confirm intro", 0, "check_user_input"),
	("Ask user to confirm no leds", 0, "check_user_input"),
	("Ask user to confirm heatbeat led", 0, "check_user_input"),
	("Ask user to insert keyfob", 0, "check_user_input"),
	(None, 0, "check_power_control_on"),
	("Ask user to confirm intro", 0, "check_user_input"),
	("Ask user to confirm batt led count", 8, "check_user_input"),
	("Ask user to confirm speed led count", 0, "check_user_input"),
	
	("Set throttles", 1, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Ask user to confirm speed led count", 0, "check_user_input"),
	
	("Set throttles", 2, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Ask user to confirm speed led count", 0, "check_user_input"),
	
	("Set throttles", 3, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Ask user to confirm speed led count", 0, "check_user_input"),
	
	("Set throttles", 0, "continue_immediately"),
	
	("Ask user to watch battery leds", 0, "check_user_input"),
	("Set power supply to volts", 495, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Set power supply to volts", 475, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Set power supply to volts", 458, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Set power supply to volts", 445, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Set power supply to volts", 434, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Set power supply to volts", 424, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Set power supply to volts", 418, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	("Set power supply to volts", 410, "continue_immediately"),
	("Delay for ms", 1000, "delay_expired"),
	
	("Ask user to confirm batt led seq", 0, "check_user_input"),
	("Ask user to confirm batt led flash", 0, "check_user_input"),
	
	("Set throttles", 1, "continue_immediately"),
	("Set speed pwm", 25, "continue_immediately"),
	("Ask user to confirm speed led count", 1, "check_user_input"),
	
	("Set throttles", 2, "continue_immediately"),
	("Set speed pwm", 50, "continue_immediately"),
	("Ask user to confirm speed led count", 2, "check_user_input"),
	
	("Set throttles", 3, "continue_immediately"),
	("Set speed pwm", 75, "continue_immediately"),
	("Ask user to confirm speed led count", 3, "check_user_input"),
	
	("Set flood sensor", 1, "continue_immediately"),
	("Ask user to confirm flood warning", 1, "check_user_input"),
	(None, 0, "check_power_control_off"),
	
	("Set flood sensor", 0, "continue_immediately"),
	("Ask user to confirm flood warning", 0, "check_user_input"),
	(None, 0, "check_power_control_on"),
	
	("Ask user to remove keyfob", 0, "check_user_input"),
	(None, 0, "check_power_control_off"),
	("Ask user to confirm batt led count", 0, "check_user_input"),
	
	("Set flood sensor", 1, "continue_immediately"),
	("Ask user to confirm flood warning", 1, "check_user_input"),
	(None, 0, "check_power_control_off"),
]

if __name__ == "__main__":

	longest_action_string = max([len(s[0]) for s in TEST_STEPS if s[0]])
	longest_test_string = max([len(s[2]) for s in TEST_STEPS])

	for i, s in enumerate(TEST_STEPS):
		action_function = s[0].lower().replace(" ", "_") if s[0] else "NULL"
		action_function = "{:{width}}".format(action_function+",", width=longest_action_string+2)

		step_param = "{:6}".format(str(s[1]) + ",")
		test_function = "{:{width}}".format(s[2], width=longest_test_string+2)
		step_number = i+1

		struct_data = "".join([action_function, step_param, test_function])
		print("\t{{{}}}, // Test {}".format(struct_data, step_number))

