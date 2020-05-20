#include "mydevices.h"
#include "core_simulation.h"
using namespace std;

// Sensors constructors
Sensor::Sensor(int delay, std::string file)
    : delay(delay), file(file) {}

AnalogSensor::AnalogSensor(int delay, std::string file)
    : Sensor(delay, file), value(0) {}

// Check if the file exists first
// If it does, opens it and reads its content :
// it's the value of the read value
void AnalogSensor::update()
{
    if (ifstream(this->file))
    {
        // the file does exist
        ifstream infile;
        std::string buffer;
        infile.open(this->file);
        infile >> buffer;
        value = std::stoi(buffer);
    }
}

void AnalogSensor::run()
{
    while (1)
    {
        update();
        if (ptrmem != NULL)
            *ptrmem = value;
        sleep(delay);
    }
}

DigitalSensor::DigitalSensor(int delay, std::string file)
    : Sensor(delay, file), state(0) {}

// Checks if the file exists
// Change the state to true if it does, false if not
void DigitalSensor::update()
{
    if (ifstream(this->file))
        state = true;
    else
        state = false;
}

void DigitalSensor::run()
{
    while (1)
    {
        update();
        if (ptrmem != NULL)
            *ptrmem = state;
        sleep(delay);
    }
}