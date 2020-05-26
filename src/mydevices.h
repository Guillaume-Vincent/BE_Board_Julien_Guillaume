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
    // Delay between two succesive updates of the sensor
    int delay;
    // File to read to gather environmental data
    std::string file;

public:
    // Initialise delay and file variables
    Sensor(int delay, std::string file);
    // Update the value of the sensor
    virtual void update() = 0;
};

class AnalogSensor : public Sensor
{
private:
    // Value read by the sensor
    int value;

public:
    // Initialise delay and file variables
    AnalogSensor(int delay, std::string file);
    // Update the value of the sensor
    virtual void update();
    // Thread representing the sensor and allowing it to operate independently of the board
    virtual void run();
};

class DigitalSensor : public Sensor
{
private:
    // Sate of the DigitalSensor (true = HIGH, flase = LOW)
    bool state;

public:
    // Initialise delay and file variables
    DigitalSensor(int delay, std::string file);
    // Update the value of the sensor
    virtual void update();
    // Thread representing the sensor and allowing it to operate independently of the board
    virtual void run();
};

class DigitalActuator : public Device
{
protected:
    // Delay between two updates of the actuator
    int delay;
    // State of the Actuator (true = HIGH, false = LOW)
    bool state;

public:
    // Initialise delay variable
    DigitalActuator(int delay);
};

class Buzzer : public DigitalActuator
{
private:
    // Audio frequency of the buzzer
    int frequency;

public:
    // Initialise delay and frequency variables
    Buzzer(int delay, int frequency);
    // Thread representing the sensor and allowing it to operate independently of the board
    virtual void run();
};

class LED : public DigitalActuator
{
private:
    // Color of the LED
    std::string color;

public:
    // Initialise delay and colorvariables
    LED(int delay, std::string color);
    // Thread representing the sensor and allowing it to operate independently of the board
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
    // Name of the exception
    deviceExcepName errorName;

public:
    // Creating the exception using its name
    DeviceException(deviceExcepName errorName);
    // Return a different text depending on the exception
    std::string text() const;
    friend std::ostream &operator<<(std::ostream &os, const DeviceException &de);
};

#endif
