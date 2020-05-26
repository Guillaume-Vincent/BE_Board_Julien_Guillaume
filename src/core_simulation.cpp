#include <thread>
#include <unistd.h>
#include <string.h>

#include "core_simulation.h"

// BoardException class
int BoardException::get() { return num; }

string BoardException::text()
{
  string s;
  switch (num)
  {
  case SPEED:
    s = string("mauvaise vitesse de la laison terminal");
    break;
  case INOUT:
    s = string("mauvaise utilisation du sens de l'entree/sortie");
    break;
  case ADDRESS:
    s = string("mauvaise adresse de la pin");
    break;
  case SIZE:
    s = string("taille erronee");
    break;
  case EMPTY:
    s = string("zone vide");
    break;
  default:
    s = string("erreur inconnue");
  }
  return s;
}

// Terminal class
void Terminal::begin(int speed)
{
  if (speed != 9600)
  {
    cerr << "wrong speed\n";
    throw BoardException(SPEED);
  }
}
void Terminal::println(string s)
{
  cout << "Serial: " << s << endl;
}

// Generic class representing a sensor/actuator
Device::Device()
{
  ptrtype = NULL;
  ptrmem = NULL;
}

void Device::run()
{
  while (1)
  {
    cout << "empty device\n";
    sleep(3);
  }
}

void Device::setPinMem(unsigned short *ptr, enum typeio *c)
{
  ptrtype = c;
  ptrmem = ptr;
}

// class representing an arduino board
void Board::run()
{
  try
  {
    setup();
    while (1)
      loop();
  }
  catch (BoardException e)
  {
    cout << "exception: " << e.get() << endl;
  }
}

void Board::pin(int p, Device &s)
{
  s.setPinMem(&io[p], &stateio[p]);
  tabthreadpin[p] = new thread(&Device::run, &s);
}

void Board::pinMode(int p, enum typeio t)
{
  stateio[p] = t;
}

void Board::digitalWrite(int i, int l)
{
  if (stateio[i] == OUTPUT)
    io[i] = l;
  else
    throw BoardException(INOUT);
}

int Board::digitalRead(int i)
{
  int result = 0;
  if (stateio[i] == INPUT)
    result = io[i];
  else
    throw BoardException(INOUT);
  return result;
}

void Board::analogWrite(int i, int l)
{
  if (stateio[i] == OUTPUT)
    io[i] = l;
  else
    throw BoardException(INOUT);
}

int Board::analogRead(int i)
{
  int result = 0;
  if (stateio[i] == INPUT)
    result = io[i];
  else
    throw BoardException(INOUT);
  return result;
}
