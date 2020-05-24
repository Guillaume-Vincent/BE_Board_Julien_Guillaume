#include "core_simulation.h"
#include "mydevices.h"

extern int luminosite_environnement;
int main()
{
    // creation d'une board
    Board esp8266;

    // achat des senseurs et actionneurs
    //TODO : exceptions si pas de fichier avec ce nom (si pas de data, renvoie -1)

    // these sensors get information about the environment
    AnalogSensor sensor_temperature(DELAY, "environment_data/temp.data", "temperature");
    AnalogSensor sensor_smoke(DELAY, "environment_data/smoke.data", "smoke");
    AnalogSensor sensor_battery(DELAY, "environment_data/battery.data", "battery");

    // the buttons
    // this button allows the user to purposely trigger the alarm
    DigitalSensor button_test(DELAY, "button_test", "test button");

    // this button allows the user to set off the alarm once it is triggered
    DigitalSensor button_reset(DELAY, "button_reset", "reset button");

    // this button allows the user to arm or disarm the alarm
    DigitalSensor button_arm(DELAY, "button_arm", "arm button");

    // LEDs
    // this led is on when the alarm is armed
    LED led_alarm_state(DELAY, "red", "alarm state");

    // this led is on when the battery goes under 20%
    LED led_low_battery(DELAY, "orange", "low battery");

    // this buzzer buzzes when the alarm is triggered
    Buzzer buzzer(DELAY, 5, "buzzer");

    // branchement des capteurs actionneurs
    esp8266.pin(0, sensor_temperature);
    esp8266.pin(1, sensor_smoke);
    esp8266.pin(2, sensor_battery);
    esp8266.pin(3, button_test);
    esp8266.pin(4, button_reset);
    esp8266.pin(5, button_arm);
    esp8266.pin(6, led_alarm_state);
    esp8266.pin(7, led_low_battery);
    esp8266.pin(8, buzzer);

    // allumage de la carte
    esp8266.run();
    return 0;
}
