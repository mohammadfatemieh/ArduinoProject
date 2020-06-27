#include <Servo.h>

// GSM PART
#include <SoftwareSerial.h>

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
String textMessage;

boolean stateNew = false;
boolean state2 = false;
Servo Myservo;
void setup() {
   Myservo.attach(9);
  Myservo.write(0);
// RTC PART
  #ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(0, 2); // D3 and D4 on ESP8266
  #else
    Wire.begin();
  #endif

  //rtc.set(0, 21, 0, 5, 11, 10, 19);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  
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
  lcd.print("RFID");
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

  // GSM SEND MESSAGE PART
  mySerial.begin(19200);
 mySerial.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
 mySerial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  // END GSM SEND MESSAGE
 
}

void loop() {
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

  if (UID.substring(1) == "25 45 EE 7A") 
  {
    if(toggleState == 0){
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCES GRANTED");
    Myservo.write(75);
    delay(5000);
    Myservo.write(0);
    digitalWrite(led_verte, HIGH);
    tone(buzzer, 1200, 100);
    delay(125);
    tone(buzzer, 1200, 100);
    delay(2000);
    digitalWrite(led_verte, LOW);
    lcd.clear();
    delay(2000);

    incoming_hour = rtc.hour();
    incoming_minute = rtc.minute();

    Serial.println(incoming_hour);
    Serial.println(incoming_minute);
    toggleState = 1;
    }
    else{
      
      
      //delay(2000);

      exit_hour = rtc.hour();
      ext_minute = rtc.minute();

      hour_spent = exit_hour - incoming_hour; 
      minute_spent = ext_minute - incoming_minute;
      
      Serial.println(exit_hour);
      Serial.println(ext_minute);
      Serial.println("\n");
      Serial.println("\n");
      Serial.println(hour_spent);
      Serial.println(minute_spent);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("HOURS SPENT: ");
      lcd.print(hour_spent);
      lcd.setCursor(0,1);
      lcd.print("MIN SPENT ");
      lcd.print(minute_spent);

      if(minute_spent < 1){
        payment = "500.00FRW";
      }else if(minute_spent > 1){
         payment = "1000.00FRW";
      }
      SENDSMS();
      delay(4000);
      SENDSMS2();
      delay(5000);
  /*
      state2 = true;
      while(state2 == true){
      receiveSMS();
      //delay(5000);
      //Myservo.write(75);     
      //delay(10000);
      state2 = false;
      }*/
      toggleState = 0;
      
    }
     
    
  }else if(UID.substring(1) == "79 CD 73 14"){
    delay(3000);
     Myservo.write(75);
    delay(3000);
    Myservo.write(75);
    delay(3000);
    Myservo.write(0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" EXIT PERMITTED ");
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




 void SENDSMS(){

  mySerial.begin(19200);

  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+250780083122\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms

  updateSerial();
  mySerial.print("ACCORDIND TO THE TIME YOU HAVE SPENT,YOU HAVE TO PAY : " + payment + "PLEASE CHECK TO THE MONITOR THE HOURS AND MINUTES SPENT" + ); //text content
  
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
  mySerial.println("AT+CMGS=\"+250783772950\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("ACCORDIND TO THE TIME YOU HAVE SPENT,YOU HAVE TO PAY : " + payment + "PLEASE CHECK TO THE MONITOR THE HOURS AND MINUTES SPENT !"); //text content
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
/*
void receiveSMS(){
if(mySerial.available()>0){
    textMessage = mySerial.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  if(textMessage.indexOf("OPEN")>=0){
    stateNew = true;

    while(stateNew == true){
    
    // Turn on relay and save current state
    Myservo.write(75);
    delay(5000);
    Myservo.write(0);
    Serial.println("parking open");  
    textMessage = "";
    delay(5000);  
    stateNew = false; 
  }
  
  }
 /* if(textMessage.indexOf("OFF")>=0){
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
}  


// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
    mySerial.println("AT+CMGS=\"+250780083122\""); 
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
}*/
