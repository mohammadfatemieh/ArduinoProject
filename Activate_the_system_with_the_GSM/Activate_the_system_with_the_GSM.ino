/**********************LIBRARIES FOR ALL MODULES********************************/
#include "Arduino.h"
#include <Servo.h>
#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Password.h> 
#include <Keypad.h>
/*********************** THE PINS ARE DEFINED HERE******************************/
#define prevTime 3
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);
SoftwareSerial SIM900(10, 8);
/*********************FOR THE KEYPAD MODULE*********************/
Password password_1 = Password( "1234" );
Password password_2 = Password( "5678" );
const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
byte pressTime = 0;
int countPress = 0;
int limitPress = 5; 

Servo Myservo;
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 9,8,7,6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,3,2, };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
/***************** FOR OTHERS PINS *********************************/
String smsCont = "";
char letter;
int redLED = 10;
int greenLED = 11;
int alarm = 12;
int relaySolenoid = 13;
int buzzer = 5;
int PIR = 2;
int PIRvalue = 0;

void setup() {
  // put your setup code here, to run once:
     Myservo.attach(9);
  Myservo.write(90);
  digitalWrite(alarm,LOW);
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print(" SYSTEM LOCKED ");
  lcd.setCursor(0, 2);
  lcd.print(" PRESS THE CODE ");
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(alarm,OUTPUT);
   pinMode(buzzer,OUTPUT);
  digitalWrite(relaySolenoid,HIGH);
 // digitalWrite(alarm,HIGH);
  pinMode(PIR, INPUT);
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

}

void loop() {
  // put your main code here, to run repeatedly:
   PIRvalue=digitalRead(PIR);
  SMSdisc();
  delay(1);
  keypad.getKey();

}
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
  Serial.print("Pressed: ");
  Serial.println(eKey);
  switch (eKey){
    case '*': checkPassword_1(); 
              break;
    case'#': checkPassword_2();
             break;       
    case'A':password_1.reset();
            password_2.reset();
            pressTime = 0;
            break;        
    default: password_1.append(eKey);
             password_2.append(eKey);
             pressTime++;     
     }
  }
}
void checkPassword_1(){
  if (password_1.evaluate()){
    lcd.setCursor(9,4);
    lcd.print(" ");
    lcd.setCursor(9,4);
    for(int i=0;i<=pressTime;i++){
      lcd.print("*");
      }
    lcd.clear();
    lcd.setCursor(0,2);
     lcd.print("  PROSSESSING...   ");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 2);
    digitalWrite(greenLED,HIGH);
    digitalWrite(redLED,LOW);
    lcd.print(" SYSTEM UNLOCKED   ");
    delay(3000);
    lcd.clear();
     } 
  else{
     while(countPress < limitPress ){
    countPress +=1;
    lcd.setCursor(9,4);
    lcd.print(" ");
    lcd.setCursor(9,4);
    for(int i=0;i<=pressTime;i++){
      lcd.print("*");
      }
   Serial.println("INVALID CODE");
    lcd.clear();
    lcd.setCursor(0,2);
     lcd.print("  INVALID CODE");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 2);
    digitalWrite(greenLED,LOW);
    digitalWrite(redLED,HIGH);
    lcd.print(" RETRY AGAIN   ");
    delay(3000);
    lcd.clear();
    if(countPress == limitPress ){
      digitalWrite(alarm,HIGH);
      sendSMS_2();
      }
    }
   }
}

void checkPassword_2(){
  if (password_2.evaluate()){
    lcd.setCursor(9,4);
    lcd.print(" ");
    lcd.setCursor(9,4);
    for(int i=0;i<=pressTime;i++){
      lcd.print("*");
      }
    lcd.clear();
    lcd.setCursor(0,2);
     lcd.print("  PROSSESSING...   ");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 2);
    digitalWrite(greenLED,HIGH);
    digitalWrite(redLED,LOW);
    lcd.print(" SYSTEM LOCKED   ");
    delay(3000);
    lcd.clear();
     } 
  else{
     while(countPress < limitPress ){
    countPress +=1;
    lcd.setCursor(9,4);
    lcd.print(" ");
    lcd.setCursor(9,4);
    for(int i=0;i<=pressTime;i++){
      lcd.print("*");
      }
   Serial.println("INVALID CODE");
    lcd.clear();
    lcd.setCursor(0,2);
    digitalWrite(greenLED,LOW);
    digitalWrite(redLED,HIGH);
     lcd.print("  INVALID CODE");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" RETRY AGAIN   ");
    delay(3000);
    lcd.clear();
     if(countPress == limitPress ){
      digitalWrite(alarm,LOW);
      sendSMS_2();
      }
     }
   }
}

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
  /*********************8 FOR SENDING THE COMMANDE TO THE ARDUINO ********************/
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
                            Myservo.write(0);
                            Serial.println("The function of the motor");
                             if(PIRvalue == HIGH){
                              sendSMS_1();
                              digitalWrite(alarm,LOW);
                                digitalWrite(buzzer,LOW);
                              }
                             
                             digitalWrite(greenLED,HIGH);
                             digitalWrite(redLED,LOW);
                             digitalWrite(relaySolenoid,LOW);
                             SMSconfirm("THE SYSTEM IS ACTIVATED");
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
    else if(letter == 'L'){
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
         }
      }
    }
  }
  /********************* FOR SENDING THE MESSAGE IF THERE IS AN INTRUDER**************/
  void sendSMS_1() {
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.println("AT + CMGS = \"+250783772950\"");
  delay(100);
  SIM900.println("HEY INTRUDER DETECTED ");
  Serial.println("Hey intruder detected ");
  delay(100);
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  delay(5000);//the time to send the message
}
/******************************* FOR SENDING THE MESSAGE IF THERE IS SOMEONE WHO PUT THE WRONG CODE FIVE TIMES******************************/
  void sendSMS_2() {
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.println("AT + CMGS = \"+250783772950\"");
  delay(100);
  SIM900.println("HEY SOMEONE PUT THE WRONG CODE ");
  Serial.println("Hey intruder detected ");
  delay(100);
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  delay(5000);//the time to send the message
}        
