// Include Software Serial library to communicate with GSM
#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;

//Create software serial object to communicate with A6
SoftwareSerial mySerial(10, 2); //A6 Tx & Rx is connected to Arduino #3 & #2

 // END PART
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 4, 3);

 
#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"


// uRTCLib rtc;
uRTCLib rtc(0x68);


#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);

int buzzer = 7;
int led_rouge = 14;
int led_verte = 15;
int toggleState = 0;
int toggleState2 = 0;
int toggleState3 = 0;

//const String key_message = "open";
int incoming_second;
int incoming_minute;
int exit_second;
int exit_minute;
int toggle_state = 0;
int second_spent;
int minute_spent;
String payment;
int pos = 0;

// Variable to store text message
String textMessage;

// Create a variable to store Lamp state
String lampState = "HIGH";
int relay = 13;
String cardName1;
String cardName2;
String cardName3;

boolean stateNew = false;
boolean state2 = false;
boolean myState = false;

// Variable to store text message
//String textMessage;

// Create a variable to store Lamp state
//Servo myservo;

  

void setup() {
  // RTC PART
  #ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(0, 2); // D3 and D4 on ESP8266
  #else
    Wire.begin();
  #endif

 // rtc.set(0, 29,19, 5,25, 10, 19);
// RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year);
  
// END RTC PART
  
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);
  
  SPI.begin();
  Serial.begin(9600);
  module_rfid.PCD_Init();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("PARKING");
  lcd.setCursor(0,1);
  lcd.print("MANAGEMENT USING");
  delay(3000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("RFID AND GSM");
  lcd.setCursor(0,1);
  lcd.print("DONE BY:");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("UWAMAHORO Mwamin");
  lcd.setCursor(0,1);
  lcd.print("UWISHEMA Stephen");
  delay(3000);
  lcd.clear();

  //servo.attach(9);  
  //servo.write(0);
  // Automatically turn on the shield
  //digitalWrite(9, HIGH);
  //delay(1000);
  //digitalWrite(9, LOW);
  //delay(5000);
  
  // Set relay as OUTPUT
  pinMode(relay, OUTPUT);
 myservo.attach(9);  
  myservo.write(0);

  // By default the relay is off
  //digitalWrite(relay, HIGH);
  
  // Initializing serial commmunication
  Serial.begin(9600); 
  mySerial.begin(19200);

  // Give time to your GSM shield log on to network
  //delay(2000);
  Serial.print("mySerial ready...");

  // AT command to set SIM900 to SMS mode
 mySerial.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  mySerial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
 
  
}

void loop(){

  if(mySerial.available()>0){
    textMessage = mySerial.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  if(textMessage.indexOf("ON")>=0){
    // Turn on relay and save current state
    digitalWrite(relay,HIGH);
       for (pos = 0; pos <= 75; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 75; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
  lampState = "ON";
    Serial.println("Relay set to ON");  
    textMessage = "";   
  }
  if(textMessage.indexOf("OFF")>=0){
    // Turn off relay and save current state
    digitalWrite(relay,LOW);
    lampState = "off"; 
    Serial.println("Relay set to OFF");
    textMessage = ""; 
  }
  if(textMessage.indexOf("STATE")>=0){
    String message = "Lamp is " + lampState;
    sendSMS(message);
    Serial.println("Lamp state resquest");
    textMessage = "";
  }
  rtc.refresh();
  //lcd.setCursor(0,0);
  lcd.print("SCAN YOUR");
  lcd.setCursor(0,1);
  lcd.print("CARD OR BADGE...");
  //delay(3000);
  //lcd.clear();

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

  if (UID.substring(1) == "F6 46 35 2C") 
  {
    if(toggleState == 0){
    cardName1 = "ALINE";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cardName1);
    lcd.setCursor(0,1);    
    lcd.print("ACCES GRANTED");
    delay(3000);
      for (pos = 0; pos <= 75; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 75; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
    digitalWrite(led_verte, HIGH);
    tone(buzzer, 1200, 100);
    delay(125);
    tone(buzzer, 1200, 100);
    delay(2000);
    digitalWrite(led_verte, LOW);
    lcd.clear();
    delay(2000);
    incoming_second = rtc.second();
    incoming_minute = rtc.minute();

    Serial.println(incoming_minute);
    Serial.println(incoming_second);
    toggleState = 1;
   SENDSMS_3();
    }
    else{
      exit_minute = rtc.minute();
      exit_second = rtc.second();
       minute_spent = exit_minute - incoming_minute;
      second_spent = exit_second -  incoming_second; 
      if(minute_spent < 2){
        payment = "500.00FRW";
      }
      if(minute_spent >= 2){
         payment = "1000.00FRW";
      }
      
      Serial.println(exit_minute);
      Serial.println(exit_second);
      Serial.println("\n");
      Serial.println("\n");
      Serial.println(minute_spent);
      Serial.println(second_spent);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(cardName1);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MIN SPENT: ");
      lcd.print(minute_spent);
      lcd.setCursor(0,1);
      lcd.print("SECOND SPENT ");
      lcd.print(second_spent);
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YOU'VE TO PAY:");
      lcd.setCursor(0,1);
      lcd.print(payment);
      SENDSMS();
      delay(1000);
      toggleState = 0;
      
    }
  }
  
  if (UID.substring(1) == "9C 13 99 E5") 
  {
    if(toggleState2 == 0){
    cardName2 = "JOHN";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cardName2);
    lcd.setCursor(0,1);    
    lcd.print("ACCES GRANTED");
    delay(3000);
      for (pos = 0; pos <= 75; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 75; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
    digitalWrite(led_verte, HIGH);
    tone(buzzer, 1200, 100);
    delay(125);
    tone(buzzer, 1200, 100);
    delay(2000);
    digitalWrite(led_verte, LOW);
    lcd.clear();
    delay(2000);
    incoming_second = rtc.second();
    incoming_minute = rtc.minute();

    Serial.println(incoming_minute);
    Serial.println(incoming_second);
    toggleState2 = 1;
   SENDSMS_4();
    }
    else{
      exit_minute = rtc.minute();
      exit_second = rtc.second();
       minute_spent = exit_minute - incoming_minute;
      second_spent = exit_second -  incoming_second; 
      if(minute_spent < 2){
        payment = "500.00FRW";
      }
      if(minute_spent >= 2){
         payment = "1000.00FRW";
      }
      
      Serial.println(exit_minute);
      Serial.println(exit_second);
      Serial.println("\n");
      Serial.println("\n");
      Serial.println(minute_spent);
      Serial.println(second_spent);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(cardName2);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MIN SPENT: ");
      lcd.print(minute_spent);
      lcd.setCursor(0,1);
      lcd.print("SECOND SPENT ");
      lcd.print(second_spent);
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YOU'VE TO PAY:");
      lcd.setCursor(0,1);
      lcd.print(payment);
      SENDSMS2();
      delay(1000);
      lcd.clear();
      toggleState2 = 0;
      
    }
  }
  if (UID.substring(1) == "59 2A 50 14") 
  {
    if(toggleState3 == 0){
    cardName3 = "PAUL";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cardName3);
    lcd.setCursor(0,1);    
    lcd.print("ACCES GRANTED");
    delay(3000);
      for (pos = 0; pos <= 75; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 75; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
    digitalWrite(led_verte, HIGH);
    tone(buzzer, 1200, 100);
    delay(125);
    tone(buzzer, 1200, 100);
    delay(2000);
    digitalWrite(led_verte, LOW);
    lcd.clear();
    delay(2000);
    incoming_second = rtc.second();
    incoming_minute = rtc.minute();

    Serial.println(incoming_minute);
    Serial.println(incoming_second);
    toggleState3 = 1;
   SENDSMS_5();
    }
    else{
      exit_minute = rtc.minute();
      exit_second = rtc.second();
       minute_spent = exit_minute - incoming_minute;
      second_spent = exit_second -  incoming_second; 
      if(minute_spent < 2){
        payment = "500.00FRW";
      }
      if(minute_spent >= 2){
         payment = "1000.00FRW";
      }
      
      Serial.println(exit_minute);
      Serial.println(exit_second);
      Serial.println("\n");
      Serial.println("\n");
      Serial.println(minute_spent);
      Serial.println(second_spent);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(cardName3);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MIN SPENT: ");
      lcd.print(minute_spent);
      lcd.setCursor(0,1);
      lcd.print("SECOND SPENT ");
      lcd.print(second_spent);
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YOU'VE TO PAY:");
      lcd.setCursor(0,1);
      lcd.print(payment);
      SENDSMS3();
      delay(1000);
      lcd.clear();
      toggleState3 = 0;
      
    }
  }
  
  
   else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCES DENIED");
    digitalWrite(led_rouge, HIGH);
    tone(buzzer, 200, 750);
    delay(2000);
    digitalWrite(led_rouge, LOW);
    lcd.clear();
  }
}  

// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
    mySerial.println("AT+CMGS=\"+250738204276\""); 
  delay(100);
  // Send the SMS
  mySerial.println(message); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  mySerial.println((char)26); 
  delay(100);
  mySerial.println();
  // Give module time to send SMS
  delay(5000);  
}
void SENDSMS(){

  mySerial.begin(19200);

  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+250726112422\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms

  updateSerial();
  mySerial.print( cardName1 + " SPENT: " + minute_spent + ":" + second_spent + " MINUTES AND SECONDS ,SO THE PERSON HAS TO PAY :" + payment); //text content
  
  updateSerial();
  mySerial.write(26);
 delay(200); 
 }
 
void SENDSMS2(){

  mySerial.begin(19200);
  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+250726112422\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
   mySerial.print( cardName2 + " SPENT: " + minute_spent + ":" + second_spent + " MINUTES AND SECONDS ,SO THE PERSON HAS TO PAY :" + payment); //text content
  updateSerial();
  mySerial.write(26);
  delay(200);
 }
 void SENDSMS3(){

  mySerial.begin(19200);
  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+250726112422\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
   mySerial.print( cardName3 + " SPENT: " + minute_spent + ":" + second_spent + " MINUTES AND SECONDS ,SO THE PERSON HAS TO PAY :" + payment); //text content
  updateSerial();
  mySerial.write(26);
  delay(200);
 }
 
 void SENDSMS_3(){

  mySerial.begin(19200);

  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+250726112422\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms

  updateSerial();
  mySerial.print( cardName1 + " HAS ENTERED IN THE PARKING"); //text content
  
  updateSerial();
  mySerial.write(26);
 delay(200); 
 }
 void SENDSMS_4(){

  mySerial.begin(19200);

  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+250726112422\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms

  updateSerial();
  mySerial.print( cardName2 + " HAS ENTERED IN THE PARKING"); //text content
  
  updateSerial();
  mySerial.write(26);
 delay(200); 
 }
 void SENDSMS_5(){

  mySerial.begin(19200);

  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+250726112422\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms

  updateSerial();
  mySerial.print( cardName3 + " HAS ENTERED IN THE PARKING"); //text content
  
  updateSerial();
  mySerial.write(26);
 delay(200); 
 }
 
  void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
