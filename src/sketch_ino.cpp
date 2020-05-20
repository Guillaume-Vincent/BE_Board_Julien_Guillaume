#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup() {
    // on configure la vitesse de la liaison
    Serial.begin(9600);
    // on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte

}

// la boucle de controle arduino
void Board::loop() {
    
}
