#include "mydevices.h"
#include "core_simulation.h"

// Sensors constructors
Sensor::Sensor(int delay, std::string file, std::string name)
    : delay(delay), file(file), name(name) {}

AnalogSensor::AnalogSensor(int delay, std::string file, std::string name)
    : Sensor(delay, file, name), value(0) {}

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

DigitalSensor::DigitalSensor(int delay, std::string file, std::string name)
    : Sensor(delay, file, name), state(LOW) {}

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

DigitalActuator::DigitalActuator(int delay, std::string name)
: delay(delay), state(LOW), name(name){}

Buzzer::Buzzer(int delay, int frequency, std::string name)
: DigitalActuator(delay, name), frequency(frequency) {}

void Buzzer::run(){
    bool oldstate = LOW;
    while (1){
        if (ptrmem != NULL)
            state = *ptrmem;
        if (oldstate != state)
        {
            if (state == LOW)
                cout << "/!\\ ALARM OFF /!\\" << endl;
            else
                cout << "/!\\ ALARM ON /!\\" << endl;
            oldstate = state;
        }
        sleep(delay);
    }
}

LED::LED(int delay, std::string color, std::string name)
: DigitalActuator(delay, name), color(color) {}

void LED::run(){
    bool oldstate = LOW;
    while (1){
        if (ptrmem != NULL)
            state = *ptrmem;
        if (oldstate != state)
        {
            if (state == LOW)
                cout << "LED OFF" << endl;
            else
                cout << "LED ON" << endl;
            oldstate = state;
        }
        sleep(delay);
    }
}