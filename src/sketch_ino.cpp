#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(2, INPUT); // Capteur luminosite
  pinMode(1, INPUT); // Capteur temperature
  pinMode(0, OUTPUT);
}

// la boucle de controle arduino
void Board::loop(){
  char buf_temperature[100];
  char buf_luminosite[100];
  int val_temperature;
  int val_luminosite;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<10;i++){
    // lecture sur la pin 2 : capteur de luminosite
    val_luminosite = analogRead(2);
    sprintf(buf_luminosite, "luminosité %d", val_luminosite);
    Serial.println(buf_luminosite);

    // lecture sur la pin 1 : capteur de temperature
    val_temperature = analogRead(1);
    sprintf(buf_temperature,"temperature %d",val_temperature);
    Serial.println(buf_temperature);

    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature et la luminosite
      sprintf(buf_temperature,"%d",val_temperature);
      sprintf(buf_luminosite, "%d", val_temperature);
      bus.write(1, buf_temperature, 100);
      bus.write(1, buf_luminosite, 100);
    }
    cpt++;
    sleep(1);
  }
// on eteint et on allume la LED
  if(bascule)
    digitalWrite(0,HIGH);
  else
    digitalWrite(0,LOW);
  bascule=1-bascule;
  
}


