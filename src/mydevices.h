#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>



class DigitalActuator : public Device
{
private:
    int delay;
    int state;

public:
    DigitalActuator(int delay);
};


#endif
