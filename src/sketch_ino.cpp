#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup()
{
    // on configure la vitesse de la liaison
    Serial.begin(9600);
    // on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte

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

// la boucle de controle arduino
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

    // Step 1 : get environmental values
    temperature = analogRead(0);
    smoke_level = analogRead(1);
    battery_level = analogRead(2);

    button_test_pressed = digitalRead(3);
    button_reset_pressed = digitalRead(4);
    button_arm_pressed = digitalRead(5);

    // Step 2 : must the alarm be stopped ?
    if (button_reset_pressed)
    {
        alarm_ringing = false;
        reset_counter = RESET_COUNTER;
    }

    // Step 3 : shall we trigger the alarm ?
    // is there a fire ?
    if (alarm_ready && (reset_counter == 0))
    {
        if ((temperature >= THRESHOLD_TEMPERATURE) || (smoke_level >= THRESHOLD_SMOKE))
        {
            // the alarm must ring
            alarm_ringing = true;
        }
    }
    // are we testing the alarm ?
    if (button_test_pressed)
        alarm_ringing = true;

    // Step 4 : shall we light the low battery led ?
    if (battery_level <= THRESHOLD_BATTERY)
        low_battery = true;
    else
        low_battery = false;

    // Step 5 : shall we light the armed led ?
    if (button_arm_pressed)
        // toggle the readiness of the alarm
        alarm_ready = true;
    else
        alarm_ready = false;

    // Step 6 : handle the outputs
    // the ringingness of the alarm
    if (alarm_ringing)
        digitalWrite(8, HIGH);
    else
        digitalWrite(8, LOW);

    // the lightness of the low battery led
    if (low_battery)
        digitalWrite(7, HIGH);
    else
        digitalWrite(7, LOW);

    // the lightness of the alarm state led
    if (alarm_ready)
        digitalWrite(6, HIGH);
    else
        digitalWrite(6, LOW);

    if (reset_counter > 0)
        reset_counter--;

    // display the environmental status
    cout << "temperature : " << temperature << endl;
    cout << "smoke : " << smoke_level << endl;
    cout << "battery : " << battery_level << endl;
    cout << "alarm ringing : " << alarm_ringing << endl;
    cout << "alarm ready : " << alarm_ready << endl;
    cout << "low battery : " << low_battery << endl;
    cout << endl;

    sleep(1);
}
