#include <Servo.h>
// GSM PART 

#include "Arduino.h"
#include<SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);
String smsCont = "";
char letter;
#define prevTime 3

// END GSM PART
char senderNumber[20];

#define PINNUMBER ""
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


#include <Wire.h>
#include "DS3231.h"

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);

int buzzer = 8;
int led_rouge = 14;
int led_verte = 15;
//const String key_message = "open";
int incoming_hour;
int incoming_minute;
int exit_hour;
int ext_minute;
int toggle_state = 0;
int hour_spent;
int minute_spent;
String payment;
//String ReceivedMessage;

//RTClib RTC;
Servo Myservo;
void setup() {
Wire.begin();
  // GSM PART

   SIM900.begin(9600);
  delay(2000);
  SIM900.println("AT+CMGF=1");
  delay(100);
   SIM900.println("AT+CNMI= 1,2,0,0,0");
   delay(100);
    SIM900.println("AT+CMGD=1,4");
    delay(1000);
    SMSconfirm("THE SYSTEM IS AVAILABLE ");
    SIM900.flush();
   delay(100);
   
  // END GSM PART
  
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(20, 4);
  SPI.begin();
  module_rfid.PCD_Init();
  lcd.print("DISPOSITIF");
  lcd.setCursor(0, 1);
  lcd.print("OF IDENTIFICATION");
  delay(3000);
  lcd.clear();
  Myservo.attach(9);
  Myservo.write(90);
}

void loop() {
//  DateTime now = RTC.now();
  lcd.print("SCAN YOUR");
  lcd.setCursor(0, 1);
  lcd.print("CARD OR BADGE..");

  if ( ! module_rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! module_rfid.PICC_ReadCardSerial()) 
  {
    return;
  }

  String UID = "";

  for (byte i = 0; i < module_rfid.uid.size; i++) {
    UID.concat(String(module_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UID.concat(String(module_rfid.uid.uidByte[i], HEX));
  }

  UID.toUpperCase();
  

  if (UID.substring(1) == "25 45 EE 7A") 
  {
     if(toggle_state= 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCES GRANTED");
    digitalWrite(led_verte, HIGH);
    tone(buzzer, 1200, 100);
    delay(125);
    tone(buzzer, 1200, 100);
    delay(2000);
    digitalWrite(led_verte, LOW);
    lcd.clear();
    incoming_hour = now.hour();
    incoming_minute = now.minute();
    Myservo.write(0);
    delay(5000);
    Myservo.write(90);
   toggle_state = 1;
    
    }
    else{
      
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PAYMENT");
    digitalWrite(led_verte, HIGH);
    tone(buzzer, 1200, 100);
    delay(125);
    tone(buzzer, 1200, 100);
    delay(2000);
    digitalWrite(led_verte, LOW);
    lcd.clear();
//    exit_hour = now.hour();
    ext_minute = now.minute();
  // calcul of how much to pay 

  hour_spent = exit_hour - incoming_hour;
  minute_spent = ext_minute - incoming_minute;

  if(minute_spent == 6){
    payment = "500.00Rwf";
  }else if(minute_spent < 3){
    payment = "1000.00Rwf";
  }

  // function to send the message first
  sendSMS_1();
  
    lcd.setCursor(0,1);
    lcd.print(hour_spent + "HOURS SPENT");
    lcd.setCursor(0,2);
    lcd.print(minute_spent + "MINUTES SPENT");
    lcd.setCursor(0,3);
    lcd.print("CHECK MESSAGE IN PHONE");

    delay(5000);
    SMSdisc();
      toggle_state= 0;
      
    }
     
  }

  else {
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("sorry you're");
    lcd.setCursor(0,1);
    lcd.print("not allowed");
    digitalWrite(led_rouge, HIGH);
    tone(buzzer, 200, 750);
    delay(2000);
    digitalWrite(led_rouge, LOW);
    lcd.clear();
  }
 
}

//gsm part


void SMSconfirm(String message){
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.println("AT + CMGS = \"+250783772950\"");
  delay(100);
  SIM900.println(message);
  Serial.println((char)26);
  delay(100);
  SIM900.println();
  delay(100);
  SIM900.println("AT + CMGD=1,4");
  delay(100);
  SIM900.println("AT + CMGF=1");
  delay(100);
  SIM900.println("AT + CNMI=1,2,0,0,0");
  delay(5000);//the time to send the message
  smsCont = "";
  }
  void SMSdisc(){
  while(SIM900.available()){
    delay(prevTime);
    letter= SIM900.read();
    if(SIM900.available()){
      delay(prevTime);
     letter = SIM900.read();
/*****************FOR ACTIVATE THE SYSTEM ********************/ 
      if(letter == 'H'){
      if(SIM900.available()){
          delay(prevTime);
          letter = SIM900.read();
          if(letter == 'I'){
  if(SIM900.available()){
              delay(prevTime);
              letter = SIM900.read();
              if(letter == 'G'){
                if(SIM900.available()){
                  delay(prevTime);
                  letter = SIM900.read();
                  if(letter == 'H'){
                     if(SIM900.available()){
                       delay(prevTime);
                        letter = SIM900.read();
                           if(letter == 'a'){

                              
                             /*if(PIRvalue == HIGH){
                              sendSMS_1();
                              //servo
                              //digitalWrite(alarm,LOW);
                                //digitalWrite(buzzer,LOW);
                              }
                             Serial.println("The function of the motor");
                             //digitalWrite(greenLED,HIGH);
                             //digitalWrite(redLED,LOW);
                            // digitalWrite(relaySolenoid,LOW);*/

                            Myservo.write(0);
                            delay(5000);
                            Myservo.write(90);
                             SMSconfirm("Barriar opened");
                             } 
                            }
                          }    
                       }
                    }
                 }
             }
        }
    }
  /********************  FOR DESACTIVATE THE SYSTEM  **************************/   
 /*   else if(letter == 'L'){
          if(SIM900.available()){
            delay(prevTime);
            letter = SIM900.read();
            if(letter =='O'){
              if(SIM900.available()){
                delay(prevTime);
                letter = SIM900.read();
                if(letter == 'W'){
                  if(SIM900.available()){
                    delay(prevTime);
                    letter = SIM900.read();
                    if(letter == 'a'){
                      if(PIRvalue == LOW){
                        digitalWrite(alarm,HIGH);
                         }
                          digitalWrite(greenLED,LOW);
                          digitalWrite(redLED,HIGH);
                          digitalWrite(relaySolenoid,HIGH);
                          smsCont = "THE SYSTEM IS DESACTIVATED";
                          SMSconfirm(smsCont);
                      
                      }
                    
                    }
                  }
                }
              }
            }
         }*/
      }
    }
  } 
  /********************* FOR SENDING THE MESSAGE IF THERE IS AN INTRUDER**************/
  void sendSMS_1() {
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.println("AT + CMGS = \"+250783772950\"");
  SIM900.println("AT + CMGS = \"+250780083122\"");
  delay(100);
  SIM900.println("hello you have to pay" +payment);
  Serial.println("hello you have to pay" +payment);
  delay(100);
  SIM900.println((char)90);
  delay(100);
  SIM900.println();
  delay(5000);//the time to send the message
}
        
