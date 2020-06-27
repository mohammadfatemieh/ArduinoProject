//#include<IRremote.h>
#include <SPI.h> // RC522 Module uses SPI protocol
#include <MFRC522.h> // Library for Mifare RC522 Devices
#include <LiquidCrystal.h>
#include<Servo.h>
#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
LiquidCrystal lcd(12,11,6,4,3,2);// the construction of LCD

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);// declaration of the module RFID
//Servo  myservo;
int pos = 0; 

int buzzer = 26;
int led_rouge = 24;
int led_verte = 25;
int togglestate = 0;
int i;
uRTCLib rtc;
int buzzerTone = 0;
int buzzerTime = 0;
#include<IRremote.h>
void setup() {
 Serial.begin(9600);
  Serial.println("Serial OK");
    //Max position: 32767

  #ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(0, 2); // D3 and D4 on ESP8266
  #else
    Wire.begin();
  #endif

  // Only used once, then disabled
   //rtc.set(30, 35, 14, 3, 15, 5, 19);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)

  rtc.set_rtc_address(0x68);

  // put your setup code here, to run once:
  pinMode(led_rouge,OUTPUT);
  pinMode(led_verte,OUTPUT);
  pinMode(buzzer,OUTPUT);
  lcd.begin(20, 4);
  SPI.begin(); // MFRC522 Hardware uses SPI protocol
  module_rfid.PCD_Init();// Initialize MFRC522 Hardware
  lcd.print("    DEVICE OF "); // For debugging purposes
  lcd.setCursor(0, 1);
  lcd.print(" INDENTIFICATION");
  delay(3000);
  lcd.clear();
 // myservo.attach(9); 
}

void loop() {
  realTimeClock();

  // put your main code here, to run repeatedly:
  lcd.print("   SCAN YOUR");
  lcd.setCursor(0, 1);
  lcd.print("CARD OR BADGE...");

  if ( ! module_rfid.PICC_IsNewCardPresent()){
    return;
    } // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
  if ( ! module_rfid.PICC_ReadCardSerial()){
    return;
    }// Select one of the cards
      
   String UID = "";// variable for stored the information give by the tag
/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
  for (byte i= 0; i < module_rfid.uid.size; i++){
     UID.concat(String(module_rfid.uid.uidByte[i] < 0*10 ? " 0" : " "));
     UID.concat(String(module_rfid.uid.uidByte[i], HEX));
    } 
     UID.toUpperCase();

   if (UID.substring(1) == "25 45 EE 7A" ){
    if (togglestate==0) {
 /************* FOR ALL OUR PROGRAM ************************/    
    
    systemUnlocked();
    digitalWrite(led_rouge, HIGH);
    togglestate=1;
     }
    else
   {
     systemlocked();
     togglestate=0;
     digitalWrite(led_rouge, LOW);
    
    }
 } else {
     
   accessdenied();
    }
}











   void systemlocked()

   {
    lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  SYSTEM LOCKED");
     digitalWrite(led_verte, HIGH);
     tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
       lcd.clear();
    }

   void accessdenied()
   {
    lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("ACCESS DENIED");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
     digitalWrite(led_rouge, LOW);
     lcd.clear();
    }
   void systemUnlocked()

   {
    
    lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("SYSTEM UNLOCKED");
     digitalWrite(led_verte, HIGH);
  // buzzertone();
  tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
     lcd.clear();
      
    }


    void realTimeClock()

    {
      rtc.refresh();
  Serial.print("RTC DateTime: ");
  lcd.setCursor(0,2);
  lcd.print(rtc.year());
  lcd.print('/');
  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.day());

  lcd.print(' ');
  lcd.setCursor(0,3);
  lcd.print(rtc.hour());
  lcd.print(':');
  lcd.print(rtc.minute());
  lcd.print(':');
  lcd.print(rtc.second());
  lcd.setCursor(8,2);
  lcd.print(" DAY: ");
  lcd.print(rtc.dayOfWeek());
  lcd.setCursor(8,3);
  lcd.print(" Temp:");
  lcd.print(rtc.temp());

  lcd.println();
}



void buzzertone()
{
 digitalWrite(led_verte, HIGH);
     tone(buzzer, 1200, 100);
     if(buzzerTone == 0)
     {
      if((millis()-buzzerTime) > 125)
      
      {
        tone(buzzer, 1200, 100);
        buzzerTone++;
        buzzerTime = millis();
        
      }
     
     }
     
     if(buzzerTone>0)
     {
      if((millis()-buzzerTime) > 2000)
      {
        digitalWrite(led_verte, LOW);
      
      }
     }
     tone(buzzer, 1200, 100);
     //delay(2000);
     digitalWrite(led_verte, LOW);
    
    lcd.clear();

  togglestate==0;
      
  
}
