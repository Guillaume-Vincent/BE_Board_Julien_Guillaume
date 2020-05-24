#include "core_simulation.h"
#include "mydevices.h"

extern int luminosite_environnement;
int main()
{
    // creation d'une board
    Board esp8266;

    // achat des senseurs et actionneurs
    //TODO : exceptions si pas de fichier avec ce nom (si pas de data, renvoie -1)
    AnalogSensor sensor_temperature(DELAY, "temp.data", "temperature");
    AnalogSensor sensor_smoke(DELAY, "smoke.data", "smoke");
    AnalogSensor sensor_battery(DELAY, "battery.data", "battery");

    // les boutons
    DigitalSensor button_test(DELAY, "button_test", "test button");
    DigitalSensor button_reset(DELAY, "button_reset", "reset button");

    // les LEDs
    LED led_alarm_state(DELAY, "red", "alarm state");
    LED led_low_battery(DELAY, "orange", "low battery");

    // le buzzer
    Buzzer buzzer(DELAY, 5, "buzzer");

    // branchement des capteurs actionneurs
    esp8266.pin(0, sensor_temperature);
    esp8266.pin(1, sensor_smoke);
    esp8266.pin(2, sensor_battery);
    esp8266.pin(3, button_test);
    esp8266.pin(4, button_reset);
    esp8266.pin(5, led_alarm_state);
    esp8266.pin(6, led_low_battery);
    esp8266.pin(7, buzzer);

    // allumage de la carte
    esp8266.run();
    return 0;
}
