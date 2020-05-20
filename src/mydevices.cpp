#include "mydevices.h"
#include "core_simulation.h"



DigitalActuator::DigitalActuator(int delay)
: delay(delay), state(LOW){

}

Buzzer::Buzzer(int delay, int frequency)
: DigitalActuator(delay), frequency(frequency){

}

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

LED::LED(int delay, std::string color)
: DigitalActuator(delay), color(color){

}

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


