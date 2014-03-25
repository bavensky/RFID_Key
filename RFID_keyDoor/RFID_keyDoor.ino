/**
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS: Pin 10
* RST: Pin 9
*
* Script is based on the script of Miguel Balboa. 
* New cardnumber is printed when card has changed. Only a dot is printed
* if card is the same.
*
* @version 0.1
* @author Henri de Jong
* @since 06-01-2013
*/

#include <SPI.h>
#include <RFID.h>
#include <LCD5110_Basic.h>
#define SS_PIN 10
#define RST_PIN 9
LCD5110 myGLCD(2,3,4,5,6);
RFID rfid(SS_PIN, RST_PIN); 
extern uint8_t SmallFont[];
// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;

void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  pinMode(A0, OUTPUT);
  myGLCD.print("Welcome", LEFT, 0);delay(2000);
}

void loop()
{  
    if (rfid.isCard()) 
    {
      if (rfid.readCardSerial()) 
      {
        if (rfid.serNum[0] != serNum0
         && rfid.serNum[1] != serNum1
         && rfid.serNum[2] != serNum2
         && rfid.serNum[3] != serNum3
         && rfid.serNum[4] != serNum4 ) 
        {
           serNum0 = rfid.serNum[0];
           serNum1 = rfid.serNum[1];
           serNum2 = rfid.serNum[2];
           serNum3 = rfid.serNum[3];
           serNum4 = rfid.serNum[4];
         int i=serNum0+serNum1+serNum2+serNum3+serNum4;
         if(i==830)
         {
           digitalWrite(A0, HIGH);
           myGLCD.clrScr();myGLCD.print("OPEN", LEFT, 0);} 
         else
         {
           digitalWrite(A0, LOW); 
           myGLCD.clrScr();myGLCD.print("error", LEFT, 0);
         } 
        } 
      }   
    rfid.halt();
    }
}

