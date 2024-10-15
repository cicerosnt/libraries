#include <PN512.h>
#include <SPI.h>

#define RST            3           //set RST      pin to be pin 3
#define SS             2           //set SS       pin to be pin 2
#define LED_EXTERNAL   12          //set an external led on pin 12

PN512 reader(SS,RST);              //create reader instace
byte serialCounter;                //init counter for first boot

void setup() {
  Serial.begin(9600);                //init Serial
  SPI.begin();                       //init SPI
  reader.PCD_Init();                 //init PN512
  reader.PCD_AntennaOn();            //turn antenna on
  pinMode(LED_BUILTIN, OUTPUT);              //set builtin LED to output
  pinMode(LED_S, OUTPUT);
}

void loop() {
  //first loop counter just so that it prints out the version and message when or if Serial Monitor is enabled 
  if(Serial && serialCounter == 0) {
    serialCounter = 1;
    reader.PCD_DumpVersionToSerial();
    Serial.println("Reader is ready, scan card or tag");
  }

  if(!reader.PICC_IsNewCardPresent()) return;   //wait for new card to be present
  if(!reader.PICC_ReadCardSerial())   return;   //read that new card 
  //ledBlink(5);                                  //indicator when the card is read

  byte cardUID[reader.uid.size];                
  byte card[4] = {0x04, 0x13, 0x95, 0x6A};      //set your card here

  for(byte i = 0; i < reader.uid.size; i++){
    cardUID[i] = reader.uid.uidByte[i];
  }
  printArrayHEX("scanned card: \t",cardUID,reader.uid.size);  //to see what card is scanned, optional 

  for(byte i = 0; i < reader.uid.size; i++){
    if(cardUID[i] != card[i]) continue;   //if the next byte does not match, break and continue to the rest of the code
    if(i == reader.uid.size - 1){       //if counter i reached the last byte 
      reader.ledBlink(200,LED_EXTERNAL);
    }
  }


  delay(50);                                    //optional delay
}
