#include <SPI.h> // RC522 Module uses SPI protocol
#include <MFRC522.h> // Library for Mifare RC522 Devices
#include <LiquidCrystal.h>
#define RST_PIN 5
#define SS_PIN 53
LiquidCrystal lcd(12,11,7,6,4,3);// the construction of LCD
MFRC522 module_rfid(SS_PIN, RST_PIN);// declaration of the module RFID
int buzzer = 8;
int led_rouge = 14;
int led_verte = 15;
int togglestate = 0;
int i;
void setup() {
 while(!UID.substring(1)){
  
  }
  // put your setup code here, to run once:
  pinMode(led_rouge,OUTPUT);
  pinMode(led_verte,OUTPUT);
  pinMode(buzzer,OUTPUT);
  lcd.begin(16, 2);
  SPI.begin(); // MFRC522 Hardware uses SPI protocol
  module_rfid.PCD_Init();// Initialize MFRC522 Hardware
  lcd.print("    DEVICE OF "); // For debugging purposes
  lcd.setCursor(0, 1);
  lcd.print(" INDENTIFICATION");
  delay(3000);
  lcd.clear();
}
int buzzerTone = 0;
int buzzerTime = 0;
void loop() {
  // put your main code here, to run repeatedly:
  lcd.print("    SCAN YOUR");
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
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("SYSTEM UNLOCKED");
     digitalWrite(led_verte, HIGH);
     tone(buzzer, 1200, 100);
     
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
    togglestate=1;
     lcd.clear();
    
     }
    else
   {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("SYSTEM LOCKED");
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
        togglestate=0;
        lcd.clear();
      }
     }
     delay(125);
     
     delay(2000);
      digitalWrite(led_verte, LOW);
     togglestate=0;
     lcd.clear();
     bool started = false;
     if(started)
     {
      hhh
      started = false;
     } else {
      
     }
    }
 } else {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("ACCESS DENIED");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
     digitalWrite(led_rouge, LOW);
     lcd.clear();
   
    }
}


   
