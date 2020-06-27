#include <SPI.h>
#include <MFRC522.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
LiquidCrystal lcd(12,11,6,4,3,2);
uRTCLib rtc;

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);

int buzzer = 24;
int led_rouge = 22;
int led_verte = 23;
int leed = 9;

int togglestate = 0;
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
  pinMode(leed,OUTPUT);
  lcd.begin(16, 2);
  SPI.begin();
  module_rfid.PCD_Init();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM LOCKED ");
  lcd.setCursor(0, 1);
  lcd.print(" INDENTIFICATION");
  delay(3000);
  lcd.clear();
}

void loop() {
  realTimeClock();
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("    SCAN YOUR");
  lcd.setCursor(0, 1);
  lcd.print("CARD OR BADGE...");

  if ( ! module_rfid.PICC_IsNewCardPresent()){
    return;
    }
  if ( ! module_rfid.PICC_ReadCardSerial()){
    return;
    }

      
   String UID = "";

  for (byte i= 0; i < module_rfid.uid.size; i++){
     UID.concat(String(module_rfid.uid.uidByte[i] < 0*10 ? " 0" : " "));
     UID.concat(String(module_rfid.uid.uidByte[i], HEX));
    }
     UID.toUpperCase();

   if (UID.substring(1) == "25 45 EE 7A" ){
     if (togglestate==0) {
      
     systemUnlocked();
      togglestate=1;
     }
    else 
   {
     systemlocked();
     togglestate=0;
     
    }
     
   }
    else{
     
    accessDenied();
   
    }
}

void systemlocked()

{
  lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  SYSTEM LOCKED  ");
     digitalWrite(led_verte, HIGH);
     tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
     lcd.clear();
     //lcd.print("  PROSSESSING...   ");
     //delay(1000);
      digitalWrite(leed, LOW);
      lcd.clear();
  }

void systemUnlocked()

{
     lcd.clear();
     lcd.setCursor(0, 0);
     
     
     lcd.print(" SYSTEM UNLOCKED   ");
     digitalWrite(led_verte, HIGH);
     
     tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
     lcd.clear();
     //lcd.print("  PROSSESSING...   ");
     //delay(1000);
      digitalWrite(leed, HIGH);
      lcd.clear();
  
  }

void accessDenied()

{
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  ACCESS DENIED    ");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
     digitalWrite(led_rouge, LOW);
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
lcd.setCursor(8,1);
  lcd.print(" Temp:");
  lcd.print(rtc.temp());

  lcd.println();

  
  }

void remoteControl()

{
  
  
  }

void lockEveryThing()
{
  
  
  
  }
