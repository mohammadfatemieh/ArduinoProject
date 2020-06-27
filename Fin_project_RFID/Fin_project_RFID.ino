#include <SPI.h> // RC522 Module uses SPI protocol
#include <MFRC522.h> // Library for Mifare RC522 Devices
#include <LiquidCrystal.h>
#include<Servo.h>
LiquidCrystal lcd(12,11,7,6,4,3);// the construction of LCD

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);// declaration of the module RFID
Servo  myservo;

int buzzer = 32;
int led_rouge = 34;
int led_verte = 35;
int togglestate = 0;
int i;
void setup() {
 
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

   if (UID.substring(1) == " 25 45 EE 7A" ){
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
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
      digitalWrite(led_verte, LOW);
     togglestate=0;
     lcd.clear();
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


   
