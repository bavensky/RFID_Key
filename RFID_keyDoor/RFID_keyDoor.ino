/*******************************************************************************
 * Project  : RFID KeyLock                                                     *
 * Compiler : Arduino 1.0.2                                                    *
 * Board    : Arduino NANO                                                     *
 * Module   : RFID Module(RC522)                                               *
 *          : LCD5110 Module                                                   *
 * Author   : Bavensky :3                                                      *
 * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
 * Date     : 25/03/2014 [dd/mm/yyyy]                                          *
 *******************************************************************************/
#include <SPI.h>
#include <RFID.h>
#include <LCD5110_Basic.h>
#define SS_PIN 10
#define RST_PIN 9
LCD5110 myGLCD(2,3,4,5,6);

RFID rfid(SS_PIN, RST_PIN); 
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
extern uint8_t logo[];
extern uint8_t welcome[];
extern uint8_t error[];
extern uint8_t view[];
extern uint8_t view2[];
extern uint8_t module[];
           
    int sum=0,i=0,serNum0,serNum1,serNum2,serNum3,serNum4;
    String str[4];

void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.drawBitmap(0, 0, logo, 84, 48);delay(2000);
  myGLCD.drawBitmap(0, 0, module, 84, 48);delay(2000);
  pinMode(A0, OUTPUT);
}

void loop()
{ 
 i=1;
  while(i==1)
  {  
    for(int m=0;m<50;m++){
    check(); 
    myGLCD.drawBitmap(0, 0, view, 84, 48);
    delay(10);
    i=2;  
  }}
  while(i==2)
  {
    for(int m=0;m<50;m++){
    check();   
    myGLCD.drawBitmap(0, 0, view2, 84, 48);
    delay(10);
    i=3;
  }}
  while(i==3)
  {
    for(int m=0;m<50;m++){
    check();   
    myGLCD.drawBitmap(0, 0, logo, 84, 48);
    delay(10);
    i=0;
  }}
}

void check()
{
  if (rfid.isCard()) 
    {
      sum=0;serNum0=0;serNum1=0;serNum2=0;serNum3=0;serNum4=0;
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
           sum = serNum0+serNum1+serNum2+serNum3+serNum4;
           
/*** Convert int to stringarray ***/
  str[0] = String(serNum0);   str[1] = String(serNum1);
  str[2] = String(serNum2);   str[3] = String(serNum3);
  str[4] = String(serNum4);
/*** stringarray to string ***/  
  String string = str[0]+str[1]+str[2]+str[3]+str[4];
  
         if(sum==830)
         {
           digitalWrite(A0, HIGH);
           myGLCD.drawBitmap(0, 0, welcome, 84, 48);delay(2000);myGLCD.clrScr();
           
           myGLCD.setFont(SmallFont);
           myGLCD.print("WELCOME !", LEFT, 0);
           myGLCD.print("Takan tanti :)", LEFT, 16);
           myGLCD.print("ID: ", LEFT, 32);
           
           myGLCD.setFont(SmallFont);
           myGLCD.print(string, LEFT, 40);
           delay(5000);
           myGLCD.clrScr();
         } 
         if(sum!=830)
         {
           digitalWrite(A0, LOW); 
           myGLCD.drawBitmap(0, 0, error, 84, 48);delay(2000);myGLCD.clrScr();
           
           myGLCD.setFont(SmallFont);
           myGLCD.print("ERROR !", LEFT, 0);
           myGLCD.print("Who are you ? :)", LEFT, 8);
           myGLCD.print(" Try again >>", LEFT, 16);
           myGLCD.print("ID: ", LEFT, 32);
           
           myGLCD.setFont(SmallFont);
           myGLCD.print(string, LEFT, 40);

           delay(5000);
           myGLCD.clrScr();
         }
        } 
      }   
    rfid.halt();
    }
    i=0;
}


