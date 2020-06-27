#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,7,6,4,3);

uRTCLib rtc;

Servo servo;

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);

int LED1 = 24 ;  //pins respectifs des LED
int LED2 = 25;
int led3 = 11;
int PIR1 = 22;   //pins respectifs des capteurs PIR 
int PIR2 = 26;
int PIR3 = 28;   //pins respectifs des capteurs PIR 
int PIR4 = 24;
int alarm1 = 48;
int remote = 37; 


boolean PIRvalue1; 
boolean PIRvalue2; 
boolean PIRvalue3; 
boolean PIRvalue4; 


int buzzer = 32;
int led_rouge = 34;
int led_verte = 35;
int leed = 9;

int togglestate = 0;
void setup() {
 
  // put your setup code here, to run once:
Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     pinMode(PIR1, INPUT);
     pinMode(PIR2, INPUT);
     pinMode(PIR3, INPUT);
     pinMode(PIR4, INPUT);

     pinMode(alarm1, OUTPUT);
     pinMode(remote, OUTPUT);

     digitalWrite(alarm1, HIGH);
     digitalWrite(remote, HIGH);
     
  
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
        Serial.println ("PIR Ready to go!");
     servo.write(50);
  
delay (2000);
lcd.begin(20,4);
  Serial.begin(9600);
  Serial.println("Serial OK");
    //Max position: 32767

  #ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(0, 2); // D3 and D4 on ESP8266
  #else
    Wire.begin();
  #endif

  // Only used once, then disabled
  // rtc.set(34, 10, 15, 2, 11, 6, 19);
  // RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)

  rtc.set_rtc_address(0x68);
  
  pinMode(led_rouge,OUTPUT);
  pinMode(led_verte,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(leed,OUTPUT);
  lcd.begin(20, 4);
  SPI.begin();
  module_rfid.PCD_Init();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM LOCKED ");
  lcd.setCursor(0, 1);
  lcd.print(" INDENTIFICATION");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);
}
int pos=0;
bool direct=false;
long prevTime=0;
bool unlocked = false;
void loop() {
  // put your main code here, to run repeatedly:
  kaka();
  if(!unlocked){
    Serial.println("leleellele");
  lcd.setCursor(0, 2);
  lcd.print("    SCAN YOUR");
  lcd.setCursor(0, 3);
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

   if (UID.substring(1) == "25 45 EE 7A" )
   {
    lcd.clear();
     lcd.setCursor(0, 2);
     
     
     lcd.print(" SYSTEM UNLOCKED   ");
     digitalWrite(led_verte, HIGH);
     
     tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
     lcd.clear();
     lcd.setCursor(0,2);
     lcd.print("  PROSSESSING...   ");
     delay(1000);
      digitalWrite(leed, HIGH);
      togglestate=1;
     lcd.clear();
     unlocked = true;
     Serial.println("system unlocked ");
   } else {
    Serial.println("invalid card");
    nana();
   }
  }
  else {



Serial.println("barack");
cervo();
digitalWrite(remote, LOW);
    
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

   if (UID.substring(1) == "25 45 EE 7A" )
   {
    lcd.clear();
     lcd.setCursor(0, 2);
     lcd.print("  SYSTEM LOCKED  ");
     digitalWrite(led_verte, HIGH);
     tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
     lcd.clear();
     lcd.setCursor(0,2);
     lcd.print("  PROSSESSING...   ");
     delay(1000);
      digitalWrite(leed, LOW);
     togglestate=0;
     lcd.clear();
     unlocked = false;
     Serial.println("system locked ");
     digitalWrite(alarm1, HIGH);
     digitalWrite(remote, HIGH);
  } else {
    Serial.println("invalid card");
    
  }
   /* else{
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  ACCESS DENIED    ");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
   
     digitalWrite(led_rouge, LOW);
     
    
     lcd.clear();
   
    }*/
    
}

}
void nana(){
      lcd.clear();
     lcd.setCursor(0, 2);
     lcd.print("  ACCESS DENIED    ");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
   
     digitalWrite(led_rouge, LOW);
     
    
     lcd.clear(); 
    }
 void kaka(){
  rtc.refresh();
  Serial.print("RTC DateTime: ");
  lcd.setCursor(0,0);
  lcd.print("DATE:  ");
  lcd.setCursor(6,0);
  lcd.print(rtc.day());
  lcd.print('/');
  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.year());

  lcd.print(' ');
  lcd.setCursor(0,1);
  lcd.print(rtc.hour());
  lcd.print(':');
  lcd.print(rtc.minute());
  lcd.print(':');
  lcd.print(rtc.second());
  lcd.print(' ');
  lcd.setCursor(13,0);
  lcd.print(" DAY: ");
  lcd.print(rtc.dayOfWeek());
  lcd.setCursor(9,1);
  lcd.print(" Temp:");
  lcd.print(rtc.temp());
  
  }
void cervo(){
  //digitalWrite(led3, HIGH);
           
            
   PIRvalue1 = digitalRead(PIR1); 
     PIRvalue2 = digitalRead(PIR2);
      PIRvalue3 = digitalRead(PIR3);
       PIRvalue4 = digitalRead(PIR4);
   if (PIRvalue1 == LOW && PIRvalue2 == LOW  && PIRvalue3 == LOW  && PIRvalue4 == LOW)
      {
  if((millis()-prevTime)>=15)
  {
    digitalWrite(alarm1, HIGH);
    prevTime=millis();
  if(pos==180)direct=true;
  if(pos==0)direct=false;
  if(direct)pos--;
  else pos++;
  servo.write(pos); 
  }
      }

else if (PIRvalue1 == HIGH && PIRvalue2 == LOW && PIRvalue3 == LOW  && PIRvalue4 == LOW ) // && désigne le "et logique" bouléenne
      { 
           digitalWrite(alarm1, LOW);
           servo.write(120);
           Serial.println("Position servo : PIR1, Motion detected");
      } 
  else if (PIRvalue1 == LOW && PIRvalue2 == HIGH && PIRvalue3 == LOW  && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
     { 
           digitalWrite(alarm1, LOW);
           servo.write(65);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
      else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == HIGH  && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
     { 
           
           digitalWrite(alarm1, LOW);
          servo.write(150);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
     else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW  && PIRvalue4 == HIGH) // && désigne le "et logique" bouléenne
     { 
           
           digitalWrite(alarm1, LOW);
           servo.write(30);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
      else if (PIRvalue1 == HIGH && PIRvalue2 == HIGH && PIRvalue3 == LOW  && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
     { 
           
          digitalWrite(alarm1, LOW); 
           servo.write(90);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
  else  
           // Instruction des LEDs pas nécessaire, bien pratique pour connaître l'état précédent 
           // car LED reste allumée jusqu'à nouvelle détection
     {
           Serial.println("No motion");
     }
      
  }
   
