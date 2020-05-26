#ifndef CORE_SIMULATEUR_H
#define CORE_SIMULATEUR_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#define DELAY 1
#define HIGH 1
#define LOW 0
#define MAX_IO_PIN 9
#define RESET_COUNTER 10
#define THRESHOLD_TEMPERATURE 50
#define THRESHOLD_SMOKE 500
#define THRESHOLD_BATTERY 20

using namespace std;

enum typeio
{
  OUTPUT,
  INPUT
};

// exceptions gerees
enum excep
{
  SPEED,
  INOUT,
  ADDRESS,
  SIZE,
  EMPTY
};
class BoardException
{
protected:
  // numero de l'exception
  int num;

public:
  BoardException(int i) : num(i) {}
  // recuperation du numero d'exception
  int get();
  // chaine expliquant l'exception
  string text();
};

// gestion de la liaison terminal
class Terminal
{
public:
  // fonction arduino : initialisation de la liaison
  void begin(int speed);
  // fonction arduino : affichage sur le terminal
  void println(string s);
};

// representation generique d'un capteur ou d'un actionneur numerique/analogique
class Device
{
protected:
  // lien avec la carte pour lire/ecrire une valeur
  unsigned short *ptrmem;
  // lien avec la carte pour savoir si c'est une pin en entree ou en sortie
  enum typeio *ptrtype;

public:
  // constructeur initialisant le minimum
  Device();
  // boucle simulant l'equipement
  virtual void run();
  // lien entre le device et la carte arduino
  void setPinMem(unsigned short *ptr, enum typeio *c);
};

// classe representant une carte arduino
class Board
{
public:
  // valeur sur les pin
  unsigned short io[MAX_IO_PIN];
  // pin d'entree ou de sortie
  enum typeio stateio[MAX_IO_PIN];
  // threads representant chaque senseur/actionneur sur le pins analogique et digitale
  thread *tabthreadpin[MAX_IO_PIN];
  // representation de la liaison terminal
  Terminal Serial;

  // simulation de la boucle de controle arduino
  void run();
  // accroachage d'un senseur/actionneur à une pin
  void pin(int p, Device &s);
  // fonction arduino : configuration d'une pin en entree ou en sortie
  void pinMode(int p, enum typeio t);
  // fonction arduino : ecriture HIGH ou LOW sur une pin
  void digitalWrite(int i, int l);
  // fonction arduino : lecture digital sur une pin
  int digitalRead(int i);
  // fonction arduino : lecture analogique sur une pin
  void analogWrite(int i, int l);
  // fonction arduino : ecriture analogique sur une pin
  int analogRead(int i);
  // fonction arduino : initialisation de la carte arduino
  void setup();
  // fonction arduino : boucle de controle de la carte arduino
  void loop();
};

#endif
