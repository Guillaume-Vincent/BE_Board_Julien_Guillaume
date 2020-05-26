#include <unistd.h>
#include "core_simulation.h"

// Arduino initialization function
void Board::setup()
{
    // Setting up the data rate
    Serial.begin(9600);

    // Fixing input and output pins according to the sensors/actuators connected to the board
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
}

// Arduino control loop
void Board::loop()
{
    static bool alarm_ringing = false;
    static bool alarm_ready = false;
    static bool low_battery = false;
    static int reset_counter = 0;

    int temperature;
    int smoke_level;
    int battery_level;

    bool button_test_pressed;
    bool button_reset_pressed;
    bool button_arm_pressed;

    // Reading environmental data
    temperature = analogRead(0);
    smoke_level = analogRead(1);
    battery_level = analogRead(2);

    button_test_pressed = digitalRead(3);
    button_reset_pressed = digitalRead(4);
    button_arm_pressed = digitalRead(5);

    // Checking if the reset button is pressed
    if (button_reset_pressed)
    {
        // The alarm must stop ringing
        alarm_ringing = false;
        // Reseting a counter after which the alarm will be able to sound again
        reset_counter = RESET_COUNTER;
    }

    // Checking if the alarm must be triggered
    // 1) In case of a fire (the reset counter must be 0 and the alarm must be armed)
    if (alarm_ready && (reset_counter == 0))
    {
        if ((temperature >= THRESHOLD_TEMPERATURE) || (smoke_level >= THRESHOLD_SMOKE))
        {
            // The alarm must ring when the temperature or the smoke levels are above their respective thresholds
            alarm_ringing = true;
        }
    }
    // 2) If the user is testing the alarm using the test button 
    if (button_test_pressed)
        alarm_ringing = true;

    // Checking if the "low battery" LED should be lit or unlit
    if (battery_level <= THRESHOLD_BATTERY)
        low_battery = true;
    else
        low_battery = false;

    // Checking if the "armed" LED should be lit or unlit
    if (button_arm_pressed)
        alarm_ready = true;
    else
        alarm_ready = false;

    // Handling the outputs
    // The buzzer
    if (alarm_ringing)
        digitalWrite(8, HIGH);
    else
        digitalWrite(8, LOW);

    // The "low battery" LED
    if (low_battery)
        digitalWrite(7, HIGH);
    else
        digitalWrite(7, LOW);

    // The "armed" LED
    if (alarm_ready)
        digitalWrite(6, HIGH);
    else
        digitalWrite(6, LOW);

    // Decrement the reset counter
    if (reset_counter > 0)
        reset_counter--;

    // Display the environmental data
    cout << "temperature : " << temperature << endl;
    cout << "smoke : " << smoke_level << endl;
    cout << "battery : " << battery_level << endl;
    cout << "alarm ringing : " << alarm_ringing << endl;

    // Display the output values
    cout << "alarm ready : " << alarm_ready << endl;
    cout << "low battery : " << low_battery << endl;
    cout << endl;

    sleep(1);
}
