#include "mydevices.h"
#include "core_simulation.h"
#include "global.h"
using namespace std;

//classe ExternalDigitalSensorButton
ExternalDigitalSensorButton::ExternalDigitalSensorButton(int t)
: Device(), temps(t) {
	stateUpdate();
}

void ExternalDigitalSensorButton::stateUpdate() {
	if(ifstream("on.txt"))
		state = true;
	else
		state = false;
}

void ExternalDigitalSensorButton::run() {
	while (1) {
		stateUpdate();
    	if (ptrmem != NULL)
    		*ptrmem = state;
    	sleep(temps);
  }
}


//classe IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t) : Device(), state(LOW), temps(t)
{
}

void IntelligentDigitalActuatorLED::run() {
	bool oldstate = LOW;
	while (1) {
	// on fait concorder l'état de la led avec l'état du pin
		if (ptrmem != NULL)
			state = *ptrmem;
		if (oldstate != state) {
			if (state == LOW) {
				cout << "LED switch OFF" << endl;
				luminosite_environnement -= 50;
			}
			else {
				cout << "LED switch ON" << endl;
				luminosite_environnement += 50;
			}
			oldstate = state;
	    }
	    sleep(temps);
	}
}

//classe AnalogSensorLight : constructeur
AnalogSensorLight::AnalogSensorLight(int delai)
    : Device(), val(luminosite_environnement), temps(delai)
{
}

void AnalogSensorLight::run()
{
  while (1)
  {
    val = luminosite_environnement;
    if (ptrmem != NULL)
      *ptrmem = val;
    sleep(temps);
  }
}

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d, int t) : Device(), val(t), temps(d)
{
  alea = 1;
}

void AnalogSensorTemperature::run()
{
  while (1)
  {
    alea = 1 - alea;
    if (ptrmem != NULL)
      *ptrmem = val + alea;
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t) : Device(), state(LOW), temps(t)
{
}

void DigitalActuatorLED::run()
{
  while (1)
  {
    if (ptrmem != NULL)
      state = *ptrmem;
    if (state == LOW)
      cout << "((((eteint))))\n";
    else
      cout << "((((allume))))\n";
    sleep(temps);
  }
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen() : Device()
{
}

void I2CActuatorScreen::run()
{
  while (1)
  {
    if ((i2cbus != NULL) && !(i2cbus->isEmptyRegister(i2caddr)))
    {
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :" << buf << endl;
    }
    sleep(1);
  }
}
