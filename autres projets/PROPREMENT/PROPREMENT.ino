/* -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
 
/********************* LIBRARIES *****************************/
#include<IRremote.h>
#include <SPI.h>
#include <Servo.h> 
#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
#include <MFRC522.h>
#include <LiquidCrystal.h>
#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);
Servo servo;
LiquidCrystal lcd(12,11,6,4,3,2);
uRTCLib rtc;
const char DIN_RECEPTEUR_INFRAROUGE=4;  //
IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);  //
/********************* PIN IDENTIFICATION ***********************/
    int relay1 = 22; 
    int relay2 = 23;
    int relay3 = 24;
    int relay4 = 25;
    int relayAlarm = 21;
    
    int relayMicrocontroller =20;
    int PIR1 = 8;                       
    int PIR2 = 7;
    int PIR3 = 26;
    int PIR4 = 27;
    int buzzer = 28;
    int led_rouge = 29;
    int led_verte = 30;
 /************ RTC PINS (SCL, SDA, VCC, GND) *****************************/
 
   


/********************* REDEFINITION IN BOOL OF PIRs ****************************/
     bool PIRvalue1; 
     bool PIRvalue2; 
     bool PIRvalue3; 
     bool PIRvalue4;

/********************** TOGGLESTATES OF THE REMOTE CONTROL *********************/
     decode_results messageRecu;  //
     int togglestate1=0;  // OFF/ON BUTTON 1 FOR THE LAMP 1
     int togglestate2=0;  // OFF/ON BUTTON 2 FOR THE LAMP 2
     int togglestate3=0;  // OFF/ON BUTTON 3 FOR THE LAMP 3
     int togglestate4=0;  // BUTTON POWER TO ACTIVATE AND DISACTIVATE THE ALARM
/******************** TOGGLE STATE OF THE RFID CARD *********************/     
     int togglestate = 0;


    
void setup() {

  /**************** HERE ARE THE CODES WHITCH ARE GOING TO BE EXECUTED ONLY ONCE *******************/
Serial.begin(9600);  //
        monRecepteurInfraRouge.enableIRIn();  //
        monRecepteurInfraRouge.blink13(true);  //
      pinMode(relay1, OUTPUT);
      pinMode(relay2, OUTPUT);
      pinMode(relay3, OUTPUT);
      pinMode(relay4, OUTPUT);
      pinMode(relayAlarm ,OUTPUT);
      pinMode(relayMicrocontroller, OUTPUT);
 /******************** INITIASATION OF THE RELAYS AT THE STATE LOW *****************/
      
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      digitalWrite(relayAlarm, HIGH);
      //digitalWrite(relay6, HIGH);
      digitalWrite(relayMicrocontroller, HIGH);
      
      #ifdef ARDUINO_ARCH_ESP8266
      Wire.begin(0, 2); // D3 and D4 on ESP8266
      #else
      Wire.begin();
      #endif

      // THIS IS THE SETTINGS OF THE REAL TIME CLOCK TO BE Only used once, then disabled
      //rtc.set(30, 35, 14, 3, 15, 5, 19);
      //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)

      rtc.set_rtc_address(0x68);
  
      Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
      servo.attach(9); // THE SERVO MOTOR IS CONNECTED TO THE PIN 9
 /********************* REDEFINITION OF PIRs SENSORS AS INPUT *********************/
      pinMode(PIR1, INPUT);
      pinMode(PIR2, INPUT);
      pinMode(PIR3, INPUT);
      pinMode(PIR4, INPUT);
     
      Serial.print ("Setting PIR sensors ");
      Serial.println ("PIR Ready to go!");
      servo.write(90); // INITIAL POSITION OF THE OF THE SERVO MOTOR AT 90 degrees
 
      pinMode(led_rouge,OUTPUT);
      pinMode(led_verte,OUTPUT);
      pinMode(buzzer,OUTPUT);
      
      lcd.begin(20, 4);
      SPI.begin();
      module_rfid.PCD_Init();
      lcd.setCursor(0, 0);
      lcd.print("SYSTEM LOCKED ");
      lcd.setCursor(0, 1);
      lcd.print(" INDENTIFICATION");
      delay(3000);
      Serial.begin(9600); 
}
     
/************************ HERE ARE FUNCTIONS OF THE SERVO MOTOR *****************/
 
     bool unlocked = false;
     int pos       = 0;
     bool direct   = false;
     long prevTime = 0;


void loop() {

/******************* HERE ARE THE CODES WITCH ARE GOING TO BE EXECUTED REPETEDLY **************/

       realTimeClock(); // THIS IS THE FIRST FUNCTION TO BE EXECUTED FOR THE REAL TIME CLOCK 
       if(!unlocked){                                     // IF THE SYSTEM IS LOCKED
        
                   lcd.setCursor(0, 0);                 // SET THE CURSOR OF THE LCD AT THE FISRT COLOM OF THE FIRST LINE
                   lcd.print("    SCAN YOUR");         //  THIST MESSAGE ASKING FOR PRESENTING THE TAG
                   lcd.setCursor(0, 1);               //
                   lcd.print("CARD OR BADGE...");    //
                   
       if ( ! module_rfid.PICC_IsNewCardPresent()){ // THE RECOGNISATION OF THE CARD OR BAGDE
       digitalWrite(led_rouge, LOW);
       return;
       }
       if ( ! module_rfid.PICC_ReadCardSerial()){     // READ THE IDENTITY OF THE CARD OR TAG IF PRESENT
       return; 
       }

       String UID = "";    // VARIABLE THAT CONTAINS THE IDENTITY OF THE TAG OR CARD
       
  /****************************** SHOW THE IDENTITY OF THE CARD IN HEXADECIMAL **************************/
  
       for (byte i= 0; i < module_rfid.uid.size; i++){                     
       UID.concat(String(module_rfid.uid.uidByte[i] < 0*10 ? " 0" : " "));
       UID.concat(String(module_rfid.uid.uidByte[i], HEX));
       }
       UID.toUpperCase();

       if (UID.substring(1) == "25 45 EE 7A" )  // IDENTITY OF THE CARD TO BE ACCEPTED(REAL TAG)
       {
       systemUnlocked();   // CALLING OF THE FUNCION OF UNCLOCKING THE SYSTEM
       }   
       else {
       accessDenied();     // CALLING OF THE  FUNCTION OF ACCESS DENIED OF THE CARD IS WRONG 
       Serial.println("invalid card");
   }
  }
       else {  // IF THE CARD PRESENTED IS CORRECT 
        
                myServo(); // CALL THE FUNCTION OF THE SERVO MOTOR TO RUN
                Serial.println("barack");
                digitalWrite(relayMicrocontroller, LOW); // ACTIVATE THE MICROCONTROLLER
 
    
      if ( ! module_rfid.PICC_IsNewCardPresent()){  // IF THE CARD IS PRESENT AGAIN 
      return;
      }
      if ( ! module_rfid.PICC_ReadCardSerial()){    // IF SO READ THE CARD AGAIN
      return;
      }

      
      String UID = "";   // THE VARIABLE TO STORE THE IDENTITY OF THE CARD ONCE READ

/**********************  SHOW THE IDENTITY OF THE CARD IN HEXADECIMAL ******************/

      for (byte i= 0; i < module_rfid.uid.size; i++){
      UID.concat(String(module_rfid.uid.uidByte[i] < 0*10 ? " 0" : " "));
      UID.concat(String(module_rfid.uid.uidByte[i], HEX));
    }
      UID.toUpperCase();

      if (UID.substring(1) == "25 45 EE 7A" ) // IF THE SAME CARD THE READ FOR THE SECOND TIME THEN
      {
      systemLocked();  // THEN CALL THE FUNCTION OF LOCKING THE SYSTEM
      } 
  
      else {  // IS THE PRESENT CARD IS WRONG THE 
      Serial.println("invalid card"); // CALL THE FUNCTION OF INVALID CARD
      digitalWrite(led_rouge, HIGH);
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


/************************ ALL THE FUNCTIONS ********************************/

    void askingForTag()

        {
  
         Serial.println("leleellele");
         lcd.setCursor(0, 0);
         lcd.print("    SCAN YOUR");
         lcd.setCursor(0, 1);
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
         }

/*********************** FUNCTIONS **********************************/

     void accessDenied()
     {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  ACCESS DENIED    ");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
     digitalWrite(led_rouge, LOW);
     lcd.clear();
     }
     
     void systemLocked()
     {  
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  SYSTEM LOCKED  ");
     digitalWrite(led_verte, HIGH);
     tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
     lcd.clear();
     lcd.print("  PROSSESSING...   ");
     delay(1000);
     togglestate=0;
     lcd.clear();
     unlocked = false;
     Serial.println("system locked ");
     }


    void systemUnlocked()
    {
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print(" SYSTEM UNLOCKED   ");
    digitalWrite(led_verte, HIGH); 
    tone(buzzer, 1200, 100);
    delay(125);
    tone(buzzer, 1200, 100);
    delay(2000);
    digitalWrite(led_verte, LOW);
    lcd.clear();
    lcd.print("  PROSSESSING...   ");
    delay(1000);
    togglestate=1;
    lcd.clear();
    unlocked = true;
    Serial.println("system unlocked ");
      
    }
    void myServo()
    {
    PIRvalue1 = digitalRead(PIR1); 
    PIRvalue2 = digitalRead(PIR2); 
    PIRvalue3 = digitalRead(PIR3); 
    PIRvalue4 = digitalRead(PIR4);
    if (PIRvalue1 == LOW && PIRvalue2 == LOW /*&& PIRvalue3 == LOW && PIRvalue4 == LOW*/)
    {
    if((millis()-prevTime)>=15)
    {
        prevTime=millis();
        if(pos==180)direct=true;
        if(pos==0)direct=false;
        if(direct)pos--;
        else pos++;
        servo.write(pos); 
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print(" NO MOTION  ");
    }
    }

    else if (PIRvalue1 == HIGH && PIRvalue2 == LOW /*&& PIRvalue3 == LOW && PIRvalue4 == LOW*/ ) 
    { 
         lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("DETECTION IN SALOON");
         digitalWrite(relayAlarm ,LOW);
         servo.write(180);
         Serial.println("Position servo : PIR1, Motion detected");
      } 
  else if (PIRvalue1 == LOW && PIRvalue2 == HIGH /* && PIRvalue3 == LOW && PIRvalue4 == LOW*/ ) 
     { 
            lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("DETECTION IN SALOON");
            digitalWrite(relayAlarm ,LOW);
            servo.write(160);
            Serial.println("Position servo : PIR2, Motion detected");
     } 
     /* else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == HIGH && PIRvalue4 == LOW ) 
     { 
            lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("DETECTION ROOM1");
            digitalWrite(relayAlarm ,LOW);
            servo.write(100);
            Serial.println("Position servo : PIR2, Motion detected");
     } 
      else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == HIGH ) 
     { 
           lcd.clear();
           lcd.setCursor(0,1);
           lcd.print("DETECTION ROOM2");
           digitalWrite(relayAlarm ,LOW);
           servo.write(50);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
      else if (PIRvalue1 == HIGH && PIRvalue2 == HIGH && PIRvalue3 == LOW && PIRvalue4 == LOW ) 
     { 
           lcd.clear();
           lcd.setCursor(0,1);
           lcd.print("DETECTION IN SALOON");
           digitalWrite(relayAlarm ,LOW);
           servo.write(90);
           Serial.println("Position servo : PIR2, Motion detected");
     } */
    
  else  
           
     {
           lcd.clear();
           lcd.setCursor(0,1);
           lcd.print("   DETECTION");
           digitalWrite(relayAlarm ,LOW);
           Serial.println("No motion");
           
     }
      
  
  }



  void realTimeClock()   // THE FUNCTION OF THE REAL TIME CLOCK

    {
          rtc.refresh();  // REFRESH THE RTC
          Serial.print("RTC DateTime: "); // 
          lcd.setCursor(0,2);
          lcd.print(rtc.year()); 
          lcd.print('/');
          lcd.print(rtc.month());
          lcd.print('/');
          lcd.print(rtc.day());

          lcd.print(' ');
          lcd.setCursor(0,3);
          lcd.print(rtc.hour());
          lcd.print(':');
          lcd.print(rtc.minute());
          lcd.print(':');
          lcd.print(rtc.second());
          lcd.setCursor(8,2);
          lcd.print(" DAY: ");
          lcd.print(rtc.dayOfWeek());
          lcd.setCursor(8,3);
          lcd.print(" Temp:");
          lcd.print(rtc.temp());
 
          lcd.println();
}


void remoteControl()

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
/******************************************************************************/
         if (messageRecu.value == 0xFF12ED)       //
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
/******************************************************************************/
         if (messageRecu.value == 0xFF12ED)      //
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
/******************************************************************************/
         if (messageRecu.value == 0xFF12ED)      //
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
/******************************************************************************/
        /* if (messageRecu.value == 0xFF12ED)   //
        {
         if(togglestate5==0)                 //
        {
         digitalWrite(relayAlarm,LOW);          //
         togglestate5=1;                   //
        }
        else
        {
        digitalWrite(relayAlarm,HIGH);       //
        togglestate5=0;                 //
        }
        }*
/******************************************************************************/
      /*   if (messageRecu.value == 0xFF12ED)    //
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
        
        
/******************************************************************************/

    //delay(500);
    monRecepteurInfraRouge.resume();   //
  
  }
 // delay(1);
}
