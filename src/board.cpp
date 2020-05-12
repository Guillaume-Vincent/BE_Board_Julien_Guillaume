#include "core_simulation.h"
#include "mydevices.h"

// Variables globales
int luminosite_environnement = 200; // Lux

int main()
{
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY,TEMP);
  DigitalActuatorLED led1(DELAY);
  I2CActuatorScreen screen;
  AnalogSensorLight luminosite(DELAY, luminosite_environnement);

  // branchement des capteurs actionneurs
  esp8266.pin(2, luminosite);
  esp8266.pin(1, temperature);
  esp8266.pin(0,led1);
  esp8266.i2c(1,screen);
  
  // allumage de la carte
  esp8266.run();
  return 0;
}

