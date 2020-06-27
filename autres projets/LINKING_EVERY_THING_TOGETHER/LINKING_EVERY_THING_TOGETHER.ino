#include <SPI.h> // RC522 Module uses SPI protocol
#include <MFRC522.h> // Library for Mifare RC522 Devices
#include <LiquidCrystal.h>
#include<Servo.h>
//#include<IRremote.h>

LiquidCrystal lcd(12,11,6,4,3,2);// the construction of LCD

/*********** LIBRARIE FOR RTC **********************/

#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h" 
uRTCLib rtc;
//const char DIN_RECEPTEUR_INFRAROUGE=4;  //
//IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);  //
/****************** LIBRARIES FOR REMOTE CONTROL   ********************************/
//const char DIN_RECEPTEUR_INFRAROUGE=4;  //
//IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);

int relay1 = 1;  //
int relay2 = 2;  //
int relay3 = 3;  //
int relay4 = 4;  //
int relay5 = 5;  //
int relay6 = 6;  //
int relay7 = 7;  //


//decode_results messageRecu;  //
/*******************************************************/

        int togglestate1=0;  //
        int togglestate2=0;  //
        int togglestate3=0;  //
        int togglestate4=0;  //
        int togglestate5=0;  //  
        int togglestate6=0;  //
        int togglestate7=0;  //
/***************** END REMOTE CONTROL ************************************/

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);// declaration of the module RFID
Servo  myservo;

int buzzer = 26;
int led_rouge = 24;
int led_verte = 25;
int togglestate = 0;
int i;

void setup() {

/************** FOR THE RTC *************************/

#ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(0, 2); // D3 and D4 on ESP8266
  #else
    Wire.begin();
  #endif

  // Only used once, then disabled
   //rtc.set(30, 35, 14, 3, 15, 5, 19);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)

  rtc.set_rtc_address(0x68);
/****************************************************/
 
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


  Serial.begin(9600);  //
       // monRecepteurInfraRouge.enableIRIn();  //
        //monRecepteurInfraRouge.blink13(true);  //

        pinMode(relay1, OUTPUT);  //
        pinMode(relay2, OUTPUT);  //
        pinMode(relay3, OUTPUT);  //
        pinMode(relay4, OUTPUT);  //
        pinMode(relay5, OUTPUT);  //
        pinMode(relay6, OUTPUT);  //
        pinMode(relay7, OUTPUT);  //

/****************************************************************/
       digitalWrite(relay1, HIGH);  //
       digitalWrite(relay2, HIGH);  //
       digitalWrite(relay4, HIGH);  //
       digitalWrite(relay5, HIGH);  //
       digitalWrite(relay6, HIGH);  //
       digitalWrite(relay7, HIGH);  //
 
}

void loop() {
  /*********** CALL THE FUNCTION OF REAL TIME CLOCK ******************/
   //realTimeClock();
   //askingForTag();
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
   accessAccepted();
   togglestate=1;
}
   else
   {
     systemLockEveryThing();
     systemLocked();
     togglestate=0;
     askingForTag();
     
    }
 } else {
     accessDenied();
   
    }
}


/********** THE FUNCTIONS *******************************/





void accessAccepted()
{
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("SYSTEM UNLOCKED");
     digitalWrite(led_verte, HIGH);
     tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
     lcd.clear();
  
  
  }
void systemLocked()
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
     lcd.clear();
  }

   void accessDenied()
   {
    
    lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("ACCESS DENIED");
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
  lcd.setCursor(0,0);
  lcd.print(rtc.year());
  lcd.print('/');
  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.day());

  lcd.print(' ');
  lcd.setCursor(0,1);
  lcd.print(rtc.hour());
  lcd.print(':');
  lcd.print(rtc.minute());
  lcd.print(':');
  lcd.print(rtc.second());
  lcd.setCursor(8,0);
  lcd.print(" DAY: ");
  lcd.print(rtc.dayOfWeek());
  lcd.setCursor(8,1);
  lcd.print(" Temp:");
  lcd.print(rtc.temp());

  lcd.println();

      
      }

/*void remoteControl()
{
  
  if (monRecepteurInfraRouge.decode(&messageRecu))      //
   {
  
      if (messageRecu.value == 0xFF02FD)           //
        {
           if(togglestate1==0)                   //
        {
          digitalWrite(relay1, LOW);           //
          togglestate1=1;                      //
        }
      else
        {
          digitalWrite(relay1, HIGH);  //
          togglestate1=0;  //
        }
        }
/**************************************************************************/
         /*if (messageRecu.value == 0xFF12ED)       //
        {
         if(togglestate2==0)                   //
        {
         digitalWrite(relay2,LOW);           //
         togglestate2=1;                    //
        }
        else
        {
        digitalWrite(relay2,HIGH);      //
        togglestate2=0;                //
        }
        }
/**************************************************************************/
        /* if (messageRecu.value == 0xFF12ED)      //
        {
         if(togglestate3==0)                  //
        {
         digitalWrite(relay3,LOW);         //
         togglestate3=1;                  //
        }
        else
        {
        digitalWrite(relay3,HIGH);  //
        togglestate3=0;  //
        }
        }
/**************************************************************************/
       /*  if (messageRecu.value == 0xFF12ED)      //
        {
         if(togglestate4==0)                   //
        {
         digitalWrite(relay4,LOW);           //
         togglestate4=1;                   //
        }
        else
        {
        digitalWrite(relay4,HIGH);    //
        togglestate4=0;              //
        }
        }
/**************************************************************************/
        /* if (messageRecu.value == 0xFF12ED)   //
        {
         if(togglestate5==0)                 //
        {
         digitalWrite(relay5,LOW);          //
         togglestate5=1;                   //
        }
        else
        {
        digitalWrite(relay5,HIGH);       //
        togglestate5=0;                 //
        }
        }
/**************************************************************************/
        /* if (messageRecu.value == 0xFF12ED)    //
        {
         if(togglestate6==0)                 //
        {
         digitalWrite(relay6,LOW);         //
         togglestate6=1;                  //
        } 
        else
        {
        digitalWrite(relay6,HIGH);    //
        togglestate6=0;              //
        }
        }
/**************************************************************************/
       /*  if (messageRecu.value == 0xFF12ED)  //
        {
         if(togglestate7==0)              //
        {
         digitalWrite(relay7,LOW);      //
         togglestate7=1;              //
        }
        else
        {
        digitalWrite(relay7,HIGH); //
        togglestate7=0;          //
        }
        }
/**************************************************************************/
    //delay(500);
   // monRecepteurInfraRouge.resume();   //
  
  //}
  //delay(1);
  //}

   void systemLockEveryThing()

   {
       digitalWrite(relay1, HIGH);  //
       digitalWrite(relay2, HIGH);  //
       digitalWrite(relay4, HIGH);  //
       digitalWrite(relay5, HIGH);  //
       digitalWrite(relay6, HIGH);  //
       digitalWrite(relay7, HIGH);  //
       //servo.write(0);
    }
   void askingForTag()

   {
    
     
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
    }
