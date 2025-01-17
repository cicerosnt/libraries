#include <Arduino.h>
#include <HardwareSerial.h>
#include "C1_Interface.h"

HardwareSerial SerialPort(0); // logs
HardwareSerial SerialPort2(2); // C1 connection

C1_Interface interface(SerialPort2);

void ckeck_status(uint16_t status)
{
  switch (status)
  {
    case 0: //success
    break;
    case 0xff:
      SerialPort.println("Timeout/No answer from the Pepper C1 - please check connection/cables");
    break;
    default:
      SerialPort.printf("Error received: 0x%04X\n", status);
    break;
  }
}

void setup()  
{
  SerialPort.begin(115200, SERIAL_8N1, 3, 1); 
  SerialPort2.begin(115200, SERIAL_8N1, 17, 16); 
}

void loop() {
  uint8_t count, type, param, uid[8], uid_len;
  char sbuff[128];
  uint8_t ubuff[128];
  uint16_t res;

  if (interface.SendDummyCommand() == 0xff)
  {
    SerialPort.println("No answer from the Pepper C1 - please check connection/cables");
    return;
  }
  SerialPort.println("Communication OK");

  ckeck_status(interface.GetTagCount(&count));
  SerialPort.printf("Get tag count: %d\n", count);
  if (count > 0)
  {
      interface.GetUid(0, &type, &param, uid, &uid_len);
      SerialPort.printf("UID (type 0x%02X):", type);
      for (uint8_t k= 0; k < uid_len; k++)
      {
        SerialPort.printf(" %02X", uid[k]);
      }
      SerialPort.println("");

      switch (type)
      {
        case 0x01:
          SerialPort.println("MIFARE Ultralight");
          break;
        case 0x02:
          SerialPort.println("MIFARE Ultralight-C");
          break;
        default:
          SerialPort.println("This is not a Mifare Ultralight TAG, read/write test not executed.");
          interface.Halt(); //turn of RF field
          sleep(3);
          return;
      }

      //mifare ultralight tests - reading 4 pages x 4 bytes
      if (interface.MU_ReadPage(5, 4, ubuff) != 0)
      {
          interface.Halt(); //turn of RF field
          SerialPort.println("Unable to read data from the tag.");
          sleep(3);
          return;        
      }
      SerialPort.printf("Read data:");
      for (uint8_t k=0; k < 16; k++)
      {
        SerialPort.printf(" %02X", ubuff[k]);
      }
      SerialPort.println("");

      SerialPort.printf("Data to write:");
      for (uint8_t k=0; k < 16; k++)
      {
        ubuff[k] = (millis()>>8 & 0xff) + k;
        SerialPort.printf(" %02X", ubuff[k]);
      }
      SerialPort.println("");

      res = interface.MU_WritePage(5, 4, ubuff);

      if (res != 0)
      {
          interface.Halt();
          SerialPort.printf("Unable to write data - error 0x%04X\r\n", res);
          sleep(3);
          return;        
      }

      SerialPort.printf("Reading...\nNew data:");
      interface.MU_ReadPage(5, 4, ubuff);
      for (uint8_t k=0; k < 16; k++)
      {
        SerialPort.printf(" %02X", ubuff[k]);
      }

      SerialPort.println("");
  }

  interface.Halt(); //turn of RF field
  SerialPort.println("Next test in 3 seconds...");
  sleep(3);
}

