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
private:
    int delay;
    std::string file;

public:
    Sensor(int delay, std::string file);
    virtual void valueUpdate() = 0;
};

class AnalogSensor : public Sensor
{
private:
    int value;

public:
    AnalogSensor(int delay, std::string file);
    virtual void valueUpdate();
    virtual void run();
};

class DigitalSensor : public Sensor
{
private:
    bool state;

public:
    DigitalSensor(int delay, std::string file);
    virtual void valueUpdate();
    virtual void run();
};

class DigitalActuator : public Device
{
private:
    int delay;
    int state;

public:
    DigitalActuator(int delay);
};

class Buzzer : public DigitalActuator
{
private:
    int frequency;

public:
    Buzzer(int frequency);
    virtual void run();
}

class LED : public DigitalActuator
{
private:
    std::string color;

public:
    LED(std::string color);
    virtual void run();
}

#endif
