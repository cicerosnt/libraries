#include <PN512.h>
#include <SPI.h>
<<<<<<< HEAD:examples/ChangeUID/ChangeUID.ino
#include <Keyboard.h>
=======
#include <PN512.h>
>>>>>>> 79c5a6feeb5a1775274d2effad1261b4497c9663:examples/MFRC522/ChangeUID/ChangeUID.ino

#define RST     3                  //set RST     pin to be pin 3
#define SS      2                  //set SS      pin to be pin 2

PN512 reader(SS,RST);             //create reader instace
byte serialCounter;

void setup() {
  Serial.begin(9600);                //init Serial
  SPI.begin();                       //init SPI
  Keyboard.begin();                  //init keyboard, if no arguments are set the default keyboard layout is EN_keyboard
  reader.PCD_Init();                 //init PN512
  reader.PCD_AntennaOn();            //turn antenna on
  pinMode(LED_BUILTIN, OUTPUT);              //set builtin LED to output
}

void loop() {
   if(Serial && serialCounter == 0) {
    serialCounter = 1;
    reader.PCD_DumpVersionToSerial();
    Serial.println("Reader is ready, scan card or tag");
  }
  if(!reader.PICC_IsNewCardPresent()) return;   //wait for new card to be present
  if(!reader.PICC_ReadCardSerial())   return;   //read that new card 
  reader.ledBlink(5,LED_BUILTIN);                                  //indicator when the card is read

  byte cardUID[reader.uid.size];

  for(byte i = 0; i < reader.uid.size; i++){
    cardUID[i] = reader.uid.uidByte[i];
  }    


  //write info to USB/Keyboard
  Keyboard.print("Card UID:\t");
  for(byte i = 0; i < reader.uid.size; i++){
    Keyboard.print(cardUID[i] < 0x10 ? "0" : "");//if byte[i] is less then 10h then print 0 else print nothing 
    Keyboard.print(cardUID[i],HEX);              //print byte[i]
    Keyboard.print(i < reader.uid.size - 1 ? ":" : "\n");
  }


  delay(50);                                //optional delay
}

