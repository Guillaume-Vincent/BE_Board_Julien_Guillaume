#include "mydevices.h"

using namespace std;

//classe IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t) : Device(), state(LOW), temps(t)
{
}

void IntelligentDigitalActuatorLED::run()
{
  while (1)
  {
    if (ptrmem != NULL)
      state = *ptrmem;

    this->toggle();

    sleep(temps);
  }
}

void IntelligentDigitalActuatorLED::toggle()
{
  extern int luminosite_environnement;
  if (this->state == 0)
  {
    this->state = 1;
    luminosite_environnement += 50;
  }
  else
  {
    this->state = 0;
    luminosite_environnement -= 50;
  }
}

//classe AnalogSensorLight : constructeur
AnalogSensorLight::AnalogSensorLight(int delai, int luminosite)
    : Device(), val(luminosite), temps(delai)
{
}

void AnalogSensorLight::run(){
  while(1){
  	if(ptrmem!=NULL)
      *ptrmem=val;
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
