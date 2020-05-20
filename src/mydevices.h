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

#endif
