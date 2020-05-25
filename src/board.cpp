#include "core_simulation.h"
#include "mydevices.h"
#include <vector>

int main()
{
    // Creating the board
    Board esp8266;

    // Creating a vector that will hold all our devices
    vector<Device *> boardDevices;

    try
    {
    	// achat des senseurs et actionneurs
    	// these sensors get information about the environment
    	boardDevices.push_back(new AnalogSensor(DELAY, "environment_data/temp.data", "temperature"));
    	boardDevices.push_back(new AnalogSensor(DELAY, "environment_data/smoke.data", "smoke"));
    	boardDevices.push_back(new AnalogSensor(DELAY, "environment_data/battery.data", "battery"));

	    // the buttons
	    // this button allows the user to purposely trigger the alarm
	    boardDevices.push_back(new DigitalSensor(DELAY, "button/test.button", "test button"));

	    // this button allows the user to set off the alarm once it is triggered
	    boardDevices.push_back(new DigitalSensor(DELAY, "button/reset.button", "reset button"));

	    // this button allows the user to arm or disarm the alarm
	    boardDevices.push_back(new DigitalSensor(DELAY, "button/arm.button", "arm button"));

	    // LEDs
	    // this led is on when the alarm is armed
	    boardDevices.push_back(new LED(DELAY, "red", "alarm state"));

	    // this led is on when the battery goes under 20%
	    boardDevices.push_back(new LED(DELAY, "orange", "low battery"));

	    // this buzzer buzzes when the alarm is triggered
	    boardDevices.push_back(new Buzzer(DELAY, 5, "buzzer"));

	    for (unsigned int i=0; i<boardDevices.size(); i++){
	    	//esp8266.pin(i, boardDevices[i]);
	    	esp8266.pin(i, *boardDevices[i]);
	    }
    }
    catch (DeviceException e)
    {
    	cout << "Erreur : " << e.text() << endl;
    	exit(0);
    }
    // allumage de la carte
    esp8266.run();
    return 0;
}
