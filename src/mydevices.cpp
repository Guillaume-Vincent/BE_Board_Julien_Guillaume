#include "mydevices.h"
#include "core_simulation.h"

// Sensor constructor
Sensor::Sensor(int delay, std::string file)
    : delay(delay), file(file) {}

// AnalogSensor constructor - Will throw an exception if file doesn't exist
AnalogSensor::AnalogSensor(int delay, std::string file)
    : Sensor(delay, file), value(0)
{
    if (!ifstream(this->file))
        throw DeviceException(NOFILE);
}

void AnalogSensor::update()
{
    // Check if file exists
    if (ifstream(this->file))
    {
        ifstream infile;
        std::string buffer;
        // Open the file
        infile.open(this->file);
        // Store its content in a buffer
        infile >> buffer;
        // Convert the buffer to an integer and store it in value
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

// DigitalSensor constructor
DigitalSensor::DigitalSensor(int delay, std::string file)
    : Sensor(delay, file), state(LOW) {}

void DigitalSensor::update()
{
    // Check if file exists and change the state of the sensor accordingly
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

// DigitalActuator constructor
DigitalActuator::DigitalActuator(int delay)
    : delay(delay), state(LOW) {}

// Buzzer constructor
Buzzer::Buzzer(int delay, int frequency)
    : DigitalActuator(delay), frequency(frequency) {}

void Buzzer::run()
{
    bool oldstate = LOW;
    while (1)
    {
        if (ptrmem != NULL)
            state = *ptrmem;
        if (oldstate != state)
        {
            // Display the new state of the alarm
            if (state == LOW)
                cout << "/!\\ ALARM OFF /!\\" << endl;
            else
                cout << "/!\\ ALARM ON - Sounding at " << frequency << "Hz /!\\" << endl;
            oldstate = state;
        }
        sleep(delay);
    }
}

// LED constructor
LED::LED(int delay, std::string color)
    : DigitalActuator(delay), color(color) {}

void LED::run()
{
    bool oldstate = LOW;
    while (1)
    {
        if (ptrmem != NULL)
            state = *ptrmem;
        if (oldstate != state)
        {
            // Display the new state of the LED
            if (state == LOW)
                cout << color << " led off" << endl;
            else
                cout << color << " led on" << endl;
            oldstate = state;
        }
        sleep(delay);
    }
}

// DeviceException constructor
DeviceException::DeviceException(deviceExcepName errorName)
    : errorName(errorName) {}

std::string DeviceException::text() const
{
    std::string s;
    switch (errorName)
    {
    case NOFILE:
        s = string("Au moins un fichier .data n'a pas été trouvé\nMerci de lancer la simulation !");
        break;
    default:
        s = string("Erreur inconnue");
    }
    return s;
}

std::ostream &operator<<(std::ostream &os, const DeviceException &de)
{
    os << "Erreur : " << de.text() << endl;
    return (os);
}
