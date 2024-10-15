#ifndef PN512_h
#define PN512_h

#include <Arduino.h>
#include "MFRC522.h"

#define LED_BUILTIN 11

class PN512: public MFRC522
{
using MFRC522::MFRC522;

public: 
   void ledBlink(int ms, int pin);
   int printArrayHEX(char *message,byte *arrayToPrint, byte len);

};

#endif // PN512_h



