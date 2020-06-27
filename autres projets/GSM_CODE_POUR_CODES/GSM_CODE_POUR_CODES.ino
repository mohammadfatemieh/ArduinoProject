#include <SoftwareSerial.h>
SoftwareSerial SIM900(7,8);
String textForSMS1;
String textForSMS2;
String textForSMS3;
String textForSMS4;

int pirsensor1 = 10;
int led = 11;
//int pirsensor2 = 3;
//int pirsensor3 = 4;
//int pirsensor4 = 5;

void setup()

{
  randomSeed(analogRead(0));
  Serial.begin(9600);
  SIM900.begin(9600);
  Serial.println(" logging time completed!");
  pinMode(pirsensor1, INPUT);
  pinMode(led,OUTPUT);
  /*pinMode(pirsensor2, INPUT);
  pinMode(pirsensor3, INPUT);
  pinMode(pirsensor4, INPUT);*/

  delay(5000);
  }

 void loop()
 {
  
  if (digitalRead(pirsensor1) == HIGH)

  {
    textForSMS1 = "\nHey, Intruder detected ";
    sendSMS(textForSMS1);
    Serial.println(textForSMS1);
    Serial.println("message sent");
    digitalWrite(led,HIGH);
    delay(8000);
    }else{
     digitalWrite(led,LOW); 
      }
    
  /*if (digitalRead(pirsensor2) == HIGH)

  {
    textForSMS2 = "\nHey, Intruder detected in the saloon";
    sendSMS(textForSMS2);
    Serial.println(textForSMS2);
    Serial.println("message sent");
    delay(8000);
    }


    if (digitalRead(pirsensor3) == HIGH)

  {
    textForSMS3 = "\nHey, Intruder detected in room number 1";
    sendSMS(textForSMS3);
    Serial.println(textForSMS3);
    Serial.println("message sent");
    delay(8000);
    }


    if (digitalRead(pirsensor4) == HIGH)

  {
    textForSMS4 = "\nHey, Intruder detected in the room number 2";
    sendSMS(textForSMS4);
    Serial.println(textForSMS4);
    Serial.println("message sent");
    delay(8000);
    }*/
  }


  void sendSMS(String message)

  {
    SIM900.print("AT+CMGF=1\r");
    delay(1000);
    SIM900.println("AT + CMGS = \"+250784165089 \"");
    delay(1000);
    SIM900.println(message);
    delay(1000);
    SIM900.println((char)34);
    delay(1000);
    SIM900.println();
    delay(100);
    
    }
