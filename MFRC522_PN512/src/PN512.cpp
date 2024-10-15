#include <Arduino.h>
#include "PN512.h"


void PN512::ledBlink(int ms, int pin){
    digitalWrite(pin, HIGH);
    delay(ms);
    digitalWrite(pin,LOW);
}


int PN512::printArrayHEX(char *message,byte *arrayToPrint, byte len){
  Serial.print(message);
  for(byte i = 0; i < len; i++){
    Serial.print(arrayToPrint[i] < 0x10 ? "0" : "");
    Serial.print(arrayToPrint[i],HEX);
    Serial.print(i < len - 1 ? ":" : "\n");
  }
  return 0;
}


