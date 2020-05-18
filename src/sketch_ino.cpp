#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup()
{
    // on configure la vitesse de la liaison
    Serial.begin(9600);
    // on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
    pinMode(4, INPUT);  // Bouton
    pinMode(2, INPUT);  // Capteur luminosite
    pinMode(1, INPUT);  // Capteur temperature
    pinMode(0, OUTPUT); // la led
}

// la boucle de controle arduino
void Board::loop()
{
    char buf_temperature[100];
    char buf_luminosite[100];
    char buf_bouton[100];
    int val_temperature;
    int val_luminosite;
    int val_bouton;
    static int cpt = 0;
    static int bascule = 0;
    int i = 0;
    for (i = 0; i < 10; i++) {
        // lecture sur la pin 4 : bouton
        val_bouton = digitalRead(4);/*
        sprintf(buf_bouton, "bouton %d", val_bouton);
        Serial.println(buf_bouton);*/

        // lecture sur la pin 2 : capteur de luminosite
        val_luminosite = analogRead(2);/*
        sprintf(buf_luminosite, "luminosité %d", val_luminosite);
        Serial.println(buf_luminosite);*/

        // lecture sur la pin 1 : capteur de temperature
        val_temperature = analogRead(1);/*
        sprintf(buf_temperature, "temperature %d", val_temperature);
        Serial.println(buf_temperature);*/

        // ecriture sur la pin 0 : LED commandée par le bouton
        digitalWrite(0, val_bouton);

        // On affiche à tour de rôle sur l'écran:
        // la température, la luminosité, et l'état du bouton
        if (cpt % 5 == 0) {
            sprintf(buf_temperature, "Temperature : %d", val_temperature);
            bus.write(1, buf_temperature, 100);
        }
        if (cpt % 5 == 1) {
            sprintf(buf_luminosite, "Luminosite : %d", val_luminosite);
            bus.write(1, buf_luminosite, 100);
        }
        if (cpt % 5 == 2) {
            sprintf(buf_bouton, "Bouton : %d", val_bouton);
            bus.write(1, buf_bouton, 100);
        }
        cpt++;
        sleep(1);
    }
}
