#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,6,4,3,2);

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);

/*    remote control  */
#include<IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE=2;  //
IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);  //
int relay1 = 40;  //
int relay2 = 42;  //
int relay3 = 38;  //
int relay4 = 36;  //
int relay5 = 37;  //
int relay6 = 46;  //
int relay7 = 44;  //

decode_results messageRecu;  //
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------

        int togglestate1=0;  //
        int togglestate2=0;  //
        int togglestate3=0;  //
        int togglestate4=0;  //
        int togglestate5=0;  //
        int togglestate6=0;  //
        int togglestate7=0;  //
//----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------

int buzzer = 24;
int led_rouge = 22;
int led_verte = 23;
int leed = 9;

int togglestate = 0;
void setup() {


/************* REMOTE CONTRIOL ******************/

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
       digitalWrite(relay2, HIGH);
       digitalWrite(relay3, HIGH);//
       digitalWrite(relay4, HIGH);  //
       digitalWrite(relay5, HIGH);  //
       digitalWrite(relay6, HIGH);  //
       digitalWrite(relay7, HIGH);  //
 
  // put your setup code here, to run once:
  pinMode(led_rouge,OUTPUT);
  pinMode(led_verte,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(leed,OUTPUT);
  lcd.begin(16, 2);
  SPI.begin();
  module_rfid.PCD_Init();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM LOCKED ");
  lcd.setCursor(0, 1);
  lcd.print(" INDENTIFICATION");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);
}
bool unlocked = false;
void loop() {
  // put your main code here, to run repeatedly:
  if(!unlocked){
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

   if (UID.substring(1) == "25 45 EE 7A" )
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
      digitalWrite(leed, HIGH);
      togglestate=1;
     lcd.clear();
     unlocked = true;
     Serial.println("system unlocked ");
   } else {
    Serial.println("invalid card");
   }
  }
  else {


REMOTE() ;
Serial.println("barack");

    
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

   if (UID.substring(1) == "25 45 EE 7A" )
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
     //lcd.print("  PROSSESSING...   ");
     //delay(1000);
      digitalWrite(leed, LOW);
     togglestate=0;
     lcd.clear();
     unlocked = false;
     Serial.println("system locked ");
  } else {
    Serial.println("invalid card");
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


void REMOTE() 
{
 if (monRecepteurInfraRouge.decode(&messageRecu))      //
   {
  
      if (messageRecu.value == 0x410807F)           //
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
         if (messageRecu.value == 0x41040BF)       //
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
         if (messageRecu.value == 0x410C03F)      //
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
         if (messageRecu.value == 0x41020DF)      //
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
         if (messageRecu.value == 0x410A05F)   //
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
         if (messageRecu.value == 0x41048B7)    //
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
         if (messageRecu.value == 0x410E01F)  //
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
  delay(1);
}

   
