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

public:
    Sensor(int delay, std::string file);
    virtual void valueUpdate() = 0;
};

class DigitalActuator : public Device
{
protected:
    int delay;
    bool state;

public:
    DigitalActuator(int delay);
};

class Buzzer : public DigitalActuator
{
private:
    int frequency;

public:
    Buzzer(int delay, int frequency);
    virtual void run();
};

class LED : public DigitalActuator
{
private:
    std::string color;

public:
    LED(int delay, std::string color);
    virtual void run();
};

#endif
