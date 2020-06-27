/******************* LIBRARIES *******************************/

#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques
#include<IRremote.h>

#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,7,6,4,3);
uRTCLib rtc;
Servo servo; //assigner l'objet "servo" comme servomoteur

/****************************  RFID PART ******************************************/








/*************************** SERVO MOTOR PART ***********************************/
int PIR1 = 2;   //pins respectifs des capteurs PIR 
int PIR2 = 3;
int PIR3 = 4;
int PIR4 = 5;


// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 
boolean PIRvalue3; 
boolean PIRvalue4; 
boolean togglestate= true;

/***************************** REMOTE CONTROL PART *******************************************/



const char DIN_RECEPTEUR_INFRAROUGE=4;  //
IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);  //
int relay1 = 1;  //
int relay2 = 2;  //
int relay3 = 3;  //
int relay4 = 4;  //
int relay5 = 5;  //
int relay6 = 6;  //
int relay7 = 7;  //

decode_results messageRecu;  //
//---------------------------------------------------
//---------------------------------------------------

        int togglestate1=0;  //
        int togglestate2=0;  //
        int togglestate3=0;  //
        int togglestate4=0;  //
        int togglestate5=0;  //  
        int togglestate6=0;  //
        int togglestate7=0;  //
//--------------------------------------------------
//--------------------------------------------------

/****************** REAL TIME CLOCK PART *******************************/




void setup()  
{
  /***********************  RFID PART ************************************/






  
  /********************* SERVO MOTOR PART ************************/
     Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     
     pinMode(PIR2, INPUT);
     pinMode(PIR2, INPUT);
     pinMode(PIR3, INPUT);
     pinMode(PIR4, INPUT);
     
     
  
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
     Serial.println ("PIR Ready to go!");
     servo.write(0); // bouger servo position initial 0 degré

/*******************************  REMOTE CONTROL PART ********************************/

       Serial.begin(9600);  //
        monRecepteurInfraRouge.enableIRIn();  //
        monRecepteurInfraRouge.blink13(true);  //
        pinMode(relay1, OUTPUT);  //
        pinMode(relay2, OUTPUT);  //
        pinMode(relay3, OUTPUT);  //
        pinMode(relay4, OUTPUT);  //
        pinMode(relay5, OUTPUT);  //
        pinMode(relay6, OUTPUT);  //
        pinMode(relay7, OUTPUT);  //

//---------------------------------------------
//---------------------------------------------
       digitalWrite(relay1, HIGH);  //
       digitalWrite(relay2, HIGH);  //
       digitalWrite(relay4, HIGH);  //
       digitalWrite(relay5, HIGH);  //
       digitalWrite(relay6, HIGH);  //
       digitalWrite(relay7, HIGH);  //

/******************** REMOTE CONTROL PART ****************************/


delay (2000);
lcd.begin(16,2);
  Serial.begin(9600);
  Serial.println("Serial OK");
    //Max position: 32767

  #ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(0, 2); // D3 and D4 on ESP8266
  #else
    Wire.begin();
  #endif

  // Only used once, then disabled
   //rtc.set(30, 35, 14, 3, 15, 5, 19);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)

  rtc.set_rtc_address(0x68);

  

 
} 
int pos=0;
bool direct=false;
long prevTime=0;


void loop()  
{

    PIRvalue1 = digitalRead(PIR1);
    PIRvalue2 = digitalRead(PIR2);
    PIRvalue3 = digitalRead(PIR3);
    PIRvalue4 = digitalRead(PIR4); 

if (togglestate= true)

{

/************************************** SERVO MOTOR AND PIR SENSORS PART *******************************/
    if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == LOW)
{
    if((millis()-prevTime)>=15)
{
    prevTime=millis();
    if(pos==180)direct=true;
    if(pos==0)direct=false;
    if(direct)pos--;
    else pos++;
    servo.write(pos); 
}
}
    else if (PIRvalue1 == HIGH && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == LOW ) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(50);
    Serial.println("Position servo : PIR1, Motion detected");
} 
    else if (PIRvalue1 == LOW && PIRvalue2 == HIGH && PIRvalue3 == LOW && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
{ 
         
    servo.write(100);
    Serial.println("Position servo : PIR2, Motion detected");
} 
    else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == HIGH && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(150);
    Serial.println("Position servo : PIR2, Motion detected");
}
    else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == HIGH) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(160);
    Serial.println("Position servo : PIR2, Motion detected");
} 
    else if (PIRvalue1 == HIGH && PIRvalue2 == HIGH ) // && désigne le "et logique" bouléenne
{ 
    servo.write(90);
    Serial.println("Position servo : PIR2, Motion detected");
}
    else    
{
    Serial.println("No motion");
}    
}

/******************************* REAL TIME CLOCK PART *********************************************/












/********************************* REMOTE CONTROL PART *************************************************/



#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques)
Servo servo; //assigner l'objet "servo" comme servomoteur


int PIR1 = 2;   //pins respectifs des capteurs PIR 
int PIR2 = 3;
int PIR3 = 4;
int PIR4 = 5;


// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 
boolean PIRvalue3; 
boolean PIRvalue4; 
boolean togglestate= true;


void setup()  
{
     Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     
     pinMode(PIR2, INPUT);
     pinMode(PIR2, INPUT);
     pinMode(PIR3, INPUT);
     pinMode(PIR4, INPUT);
     
     
  
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
     Serial.println ("PIR Ready to go!");
     servo.write(0); // bouger servo position initial 50 degrés  
} 

int pos=0;
bool direct=false;
long prevTime=0;


void loop()  
{

  
    PIRvalue1 = digitalRead(PIR1);
    PIRvalue2 = digitalRead(PIR2);
    PIRvalue3 = digitalRead(PIR3);
    PIRvalue4 = digitalRead(PIR4); 

if (togglestate= true)

{

/************************************** SERVO MOTOR AND PIR SENSORS PART *******************************/
    if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == LOW)
{
    if((millis()-prevTime)>=15)
{
    prevTime=millis();
    if(pos==180)direct=true;
    if(pos==0)direct=false;
    if(direct)pos--;
    else pos++;
    servo.write(pos); 
}
}
    else if (PIRvalue1 == HIGH && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == LOW ) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(50);
    Serial.println("Position servo : PIR1, Motion detected");
} 
    else if (PIRvalue1 == LOW && PIRvalue2 == HIGH && PIRvalue3 == LOW && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
{ 
         
    servo.write(100);
    Serial.println("Position servo : PIR2, Motion detected");
} 
    else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == HIGH && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(150);
    Serial.println("Position servo : PIR2, Motion detected");
}
    else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == HIGH) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(160);
    Serial.println("Position servo : PIR2, Motion detected");
} 
    else if (PIRvalue1 == HIGH && PIRvalue2 == HIGH ) // && désigne le "et logique" bouléenne
{ 
    servo.write(90);
    Serial.println("Position servo : PIR2, Motion detected");
}
    else    
{
    Serial.println("No motion");
}    
}

/******************************* REAL TIME CLOCK PART *********************************************/


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

  //delay(1000);

/********************************* REMOTE CONTROL PART *************************************************/


#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques)
Servo servo; //assigner l'objet "servo" comme servomoteur


int PIR1 = 2;   //pins respectifs des capteurs PIR 
int PIR2 = 3;
int PIR3 = 4;
int PIR4 = 5;


// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 
boolean PIRvalue3; 
boolean PIRvalue4; 
boolean togglestate= true;


void setup()  
{
     Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     
     pinMode(PIR2, INPUT);
     pinMode(PIR2, INPUT);
     pinMode(PIR3, INPUT);
     pinMode(PIR4, INPUT);
     
     
  
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
     Serial.println ("PIR Ready to go!");
     servo.write(0); // bouger servo position initial 50 degrés  
} 
int pos=0;
bool direct=false;
long prevTime=0;


void loop()  
{

    PIRvalue1 = digitalRead(PIR1);
    PIRvalue2 = digitalRead(PIR2);
    PIRvalue3 = digitalRead(PIR3);
    PIRvalue4 = digitalRead(PIR4); 

if (togglestate= true)

{

/************************************** SERVO MOTOR AND PIR SENSORS PART *******************************/
    if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == LOW)
{
    if((millis()-prevTime)>=15)
{
    prevTime=millis();
    if(pos==180)direct=true;
    if(pos==0)direct=false;
    if(direct)pos--;
    else pos++;
    servo.write(pos); 
}
}
    else if (PIRvalue1 == HIGH && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == LOW ) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(50);
    Serial.println("Position servo : PIR1, Motion detected");
} 
    else if (PIRvalue1 == LOW && PIRvalue2 == HIGH && PIRvalue3 == LOW && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
{ 
         
    servo.write(100);
    Serial.println("Position servo : PIR2, Motion detected");
} 
    else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == HIGH && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(150);
    Serial.println("Position servo : PIR2, Motion detected");
}
    else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == HIGH) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(160);
    Serial.println("Position servo : PIR2, Motion detected");
} 
    else if (PIRvalue1 == HIGH && PIRvalue2 == HIGH ) // && désigne le "et logique" bouléenne
{ 
    servo.write(90);
    Serial.println("Position servo : PIR2, Motion detected");
}
    else    
{
    Serial.println("No motion");
}    
}

/******************************* REAL TIME CLOCK PART *********************************************/












/********************************* REMOTE CONTROL PART *************************************************/




void setup() 
{
        Serial.begin(9600);  //
        monRecepteurInfraRouge.enableIRIn();  //
        monRecepteurInfraRouge.blink13(true);  //
        pinMode(relay1, OUTPUT);  //
        pinMode(relay2, OUTPUT);  //
        pinMode(relay3, OUTPUT);  //
        pinMode(relay4, OUTPUT);  //
        pinMode(relay5, OUTPUT);  //
        pinMode(relay6, OUTPUT);  //
        pinMode(relay7, OUTPUT);  //

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
       digitalWrite(relay1, HIGH);  //
       digitalWrite(relay2, HIGH);  //
       digitalWrite(relay4, HIGH);  //
       digitalWrite(relay5, HIGH);  //
       digitalWrite(relay6, HIGH);  //
       digitalWrite(relay7, HIGH);  //
 

}

void loop() 
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
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)   //
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
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)    //
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
//----------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)  //
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
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------

    //delay(500);
    monRecepteurInfraRouge.resume();   //
  
  }
  //delay(1);
}






 }







 }






 }
