#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>

class Sensor : public Device
{
protected:
    int delay;
    std::string file;
    std::string name;

public:
    Sensor(int delay, std::string file, std::string name);
    // updates the value of the sensor
    virtual void update();
    virtual void run();
};

class AnalogSensor : public Sensor
{
private:
    int value;

public:
    AnalogSensor(int delay, std::string file, std::string name);
    virtual void update();
    virtual void run();
};

class DigitalSensor : public Sensor
{
private:
    bool state;

public:
    DigitalSensor(int delay, std::string file, std::string name);
    virtual void update();
    virtual void run();
};

class DigitalActuator : public Device
{
protected:
    int delay;
    bool state;
    std::string name;

public:
    DigitalActuator(int delay, std::string name);
};

class Buzzer : public DigitalActuator
{
private:
    int frequency;

public:
    Buzzer(int delay, int frequency, std::string name);
    virtual void run();
};

class LED : public DigitalActuator
{
private:
    std::string color;

public:
    LED(int delay, std::string color, std::string name);
    virtual void run();
};

// List of exceptions we can handle
enum deviceExcepName
{
    NOFILE
};

// Management of device exceptions
class DeviceException
{
private:
    deviceExcepName e;
public:
  DeviceException(deviceExcepName e);
  std::string text();
};

#endif
