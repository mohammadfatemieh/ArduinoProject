#include <uRTCLib.h>

#include <Servo.h>
// GSM PART
#include <GSM.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900A(10,11);
GSM gsmAccess;
GSM_SMS sms;
char senderNumber[20];

#define PINNUMBER ""
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


#include <Wire.h>
#include "DS3231.h"

#define RST_PIN 9
#define SS_PIN 10
MFRC522 module_rfid(SS_PIN, RST_PIN);

int buzzer = 8;
int led_rouge = 14;
int led_verte = 15;
const String key_message = "open";
int incoming_hour;
int incoming_minute;
int exit_hour;
int ext_minute;
int toggle_state = 0;
int hour_spent;
int minute_spent;
String payment;
String ReceivedMessage;

//RTClib RTC;
Servo Myservo;
void setup() {
Wire.begin();
  // GSM PART

  SIM900A.begin(9600);
  
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(20, 4);
  SPI.begin();
  module_rfid.PCD_Init();
  lcd.print("Dispositif");
  lcd.setCursor(0, 1);
  lcd.print("d'identification");
  delay(3000);
  lcd.clear();
  Myservo.attach(9);
  Myservo.write(90);
}

void loop() {
  DateTime now = RTC.now();
  lcd.print("Scannez votre");
  lcd.setCursor(0, 1);
  lcd.print("carte ou badge..");

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
  

  if (UID.substring(1) == "03 B0 0B ED") 
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
    lcd.print("payment");
    digitalWrite(led_verte, HIGH);
    tone(buzzer, 1200, 100);
    delay(125);
    tone(buzzer, 1200, 100);
    delay(2000);
    digitalWrite(led_verte, LOW);
    lcd.clear();
    exit_hour = now.hour();
    ext_minute = now.minute();
  // calcul of how much to pay 

   hour_spent = exit_hour - incoming_hour;
  minute_spent = ext_minute - incoming_minute;

  if(hour_spent <= 1 && minute_spent <=60){
    payment = "500.00Rwf";
  }else if(hour_spent > 1 && hour_spent <3 && minute_spent <=60){
    payment = "1000.00Rwf";
  }else if(hour_spent == 3 && minute_spent <=60){
    payment = "1500.00Rwf";
  }else if(hour_spent > 3 && minute_spent <=60){
    payment = "2000.00Rwf";
  }
    lcd.setCursor(0,1);
    lcd.print(hour_spent+ "hours spent");
    lcd.setCursor(0,2);
    lcd.print(minute_spent+ "minutes spent");
    lcd.setCursor(0,3);
    lcd.print("check message on phone");
   // SendMessage();
  //  ReceiveMessage();
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

/*void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+250780083122\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println(payment);// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z      
  delay(1000);
  Serial.println ("Message has been sent ->SMS Selesai dikirim");
}
/* void RecieveMessage()
{
  Serial.println ("SIM900A Membaca SMS");
  delay (1000);
  SIM900A.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  Serial.write ("Unread Message done");
 }
*/
/* void ReceiveMessage(){
  

  // If there are any SMSs available()
  if (sms.available()) {
    Serial.println("Message received from:");

    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    Serial.println(senderNumber);

    // An example of message disposal
    // Any messages starting with # should be discarded
    if (sms.peek() == '#') {
      Serial.println("Discarded SMS");
      sms.flush();
    }

    // Read message bytes and print them
    while (ReceivedMessage = sms.read()) {
      Serial.print(ReceivedMessage);

      if(ReceivedMessage == key_message){
         Myservo.write(0);
         delay(5000);
         Myservo.write(90);
      }
    }

    Serial.println("\nEND OF MESSAGE");

    // Delete message from modem memory
    sms.flush();
    Serial.println("MESSAGE DELETED");
  }

  delay(1000);

}
 */
