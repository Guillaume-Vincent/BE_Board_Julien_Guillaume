#include "mydevices.h"
#include "core_simulation.h"

// Sensor constructor
Sensor::Sensor(int delay, std::string file, std::string name)
    : delay(delay), file(file), name(name) {}


// AnalogSensor constructor - Will throw an exception if file doesn't exist
AnalogSensor::AnalogSensor(int delay, std::string file, std::string name)
    : Sensor(delay, file, name), value(0) {
        if (!ifstream(this->file))
            throw DeviceException(NOFILE);
    }

void AnalogSensor::update()
{
    // todo : exception : if bad argument do nothing and wait for the next one
    // if bad argument too many times, stop the program and alert the user

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
DigitalSensor::DigitalSensor(int delay, std::string file, std::string name)
    : Sensor(delay, file, name), state(LOW) {}

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
DigitalActuator::DigitalActuator(int delay, std::string name)
    : delay(delay), state(LOW), name(name) {}


// Buzzer constructor
Buzzer::Buzzer(int delay, int frequency, std::string name)
    : DigitalActuator(delay, name), frequency(frequency) {}

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
                cout << "/!\\ ALARM ON /!\\" << endl;
            oldstate = state;
        }
        sleep(delay);
    }
}


// LED constructor
LED::LED(int delay, std::string color, std::string name)
    : DigitalActuator(delay, name), color(color) {}

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
                cout << name << " off" << endl;
            else
                cout << name << " on" << endl;
            oldstate = state;
        }
        sleep(delay);
    }
}


// DeviceException constructor
DeviceException::DeviceException(deviceExcepName e)
    : e(e) {}

std::string DeviceException::text(){
  std::string s;
  switch (e)
  {
  case NOFILE:
    s = string("Le fichier spécifié n'a pas été trouvé");
    break;
  default:
    s = string("Erreur inconnue");
  }
  return s;
}
