#include "core_simulation.h"
#include "mydevices.h"
#include <vector>

int main()
{
	// Creating the board
	Board esp8266;

	// Creating a vector that will hold all our devices
	vector<Device *> boardDevices;

	// Setting up all our devices and putting them in a vector
	try
	{
		// Analog Sensors will gather data about the environment (temperature, smoke and battery levels)
		boardDevices.push_back(new AnalogSensor(DELAY, "environment_data/temp.data"));
		boardDevices.push_back(new AnalogSensor(DELAY, "environment_data/smoke.data"));
		boardDevices.push_back(new AnalogSensor(DELAY, "environment_data/battery.data"));

		// Buttons allow the user to interact with the other devices (test, reset, or arm/disarm the alarm)
		boardDevices.push_back(new DigitalSensor(DELAY, "button/test.button"));
		boardDevices.push_back(new DigitalSensor(DELAY, "button/reset.button"));
		boardDevices.push_back(new DigitalSensor(DELAY, "button/arm.button"));

		// LEDs will indicate the different status of the other devices (alarm ready, low battery)
		boardDevices.push_back(new LED(DELAY, "red"));		// Alarm ready LED
		boardDevices.push_back(new LED(DELAY, "orange"));   // Low battery LED

		// The buzzer sounds when the alarm is triggered
		boardDevices.push_back(new Buzzer(DELAY, 500));

		// Connecting every device to a pin of the board
		for (unsigned int i = 0; i < boardDevices.size(); i++)
			esp8266.pin(i, *boardDevices[i]);
		// Setting every io to zero 
		esp8266.razio();
	}
	catch (DeviceException e)
	{
		cout << e;
		exit(0);
	}

	// Switching the board on
	esp8266.run();
	return 0;
}
