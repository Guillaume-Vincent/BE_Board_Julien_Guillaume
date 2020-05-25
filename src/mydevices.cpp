#include "mydevices.h"
#include "core_simulation.h"

// Sensors constructors
Sensor::Sensor(int delay, std::string file, std::string name)
    : delay(delay), file(file), name(name) {}

void Sensor::run()
{
  while (1)
  {
    cout << "empty sensor\n";
    sleep(3);
  }
}

void Sensor::update()
{
    while (1)
    {
        cout << "Sensor Update\n";
        sleep(3);
    }
}

AnalogSensor::AnalogSensor(int delay, std::string file, std::string name)
    : Sensor(delay, file, name), value(0) {
        if (!ifstream(this->file))
            throw DeviceException(NOFILE);
    }

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
        // todo : exception : if bad argument do nothing and wait for the next one
        // if bad argument too many times, stop the program and alert the user
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
    : delay(delay), state(LOW), name(name) {}

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

void LED::run()
{
    bool oldstate = LOW;
    while (1)
    {
        if (ptrmem != NULL)
            state = *ptrmem;
        if (oldstate != state)
        {
            if (state == LOW)
                cout << name << " off" << endl;
            else
                cout << name << " on" << endl;
            oldstate = state;
        }
        sleep(delay);
    }
}

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