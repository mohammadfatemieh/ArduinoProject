#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques)
Servo servo;
LiquidCrystal lcd(12,11,7,6,4,3);
int LED1 = 8 ;  //pins respectifs des LED
int LED2 = 10;
int led3 = 11;
int PIR1 = 2;   //pins respectifs des capteurs PIR 
int PIR2 = 3;
// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 



#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);

int buzzer = 8;
int led_rouge = 14;
int led_verte = 15;
int leed = 9;

bool togglestate = false;
void setup() {
  Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     pinMode(PIR1, INPUT);
     pinMode(PIR2, INPUT);
     pinMode(led3, OUTPUT);
     pinMode(LED1, OUTPUT);
     pinMode(LED2, OUTPUT);
  
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
     
    
    /* for(int c = 0; c < 15; c++)// calibrer PIR jusqu'à 15 sec
           {  
                Serial.print(".");
                delay(1000); 
           } */
     Serial.println ("PIR Ready to go!");
     servo.write(0); // bouger servo position initial 50 degrés  
 
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
  
// put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("    SCAN YOUR");
  lcd.setCursor(0, 1);
  lcd.print("CARD OR BADGE...");

  
}

  /*****************************************************************************************************************************************************/

int pos=0;
bool direct=false;
long prevTime=0;

void loop() {
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

   if (UID.substring(1) == "25 45 EE 7A" ){
     if (togglestate==false) {
      
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
      togglestate=true;
     lcd.clear();
    
     }
    else 
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
      digitalWrite(leed, LOW);
     togglestate=false;
     lcd.clear();
    }
     
   }
    else{
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  ACCESS DENIED    ");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
   
     digitalWrite(led_rouge, LOW);
     
    
     lcd.clear();
   
    }

   }















































  /* while (togglestate= true )
  {
    
   PIRvalue1 = digitalRead(PIR1); 
     PIRvalue2 = digitalRead(PIR2);
   if (PIRvalue1 == LOW && PIRvalue2 == LOW)
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

 
  
 
  else if (PIRvalue1 == HIGH && PIRvalue2 == LOW ) // && désigne le "et logique" bouléenne
      { 
           digitalWrite(LED1, HIGH);
           digitalWrite(LED2, LOW);
           
           servo.write(180);
           Serial.println("Position servo : PIR1, Motion detected");
      } 
  else if (PIRvalue1 == LOW && PIRvalue2 == HIGH ) // && désigne le "et logique" bouléenne
     { 
           digitalWrite(LED1, LOW);
           digitalWrite(LED2, HIGH);
           
           servo.write(90);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
      else if (PIRvalue1 == HIGH && PIRvalue2 == HIGH ) // && désigne le "et logique" bouléenne
     { 
           
           servo.write(90);
           Serial.println("Position servo : PIR2, Motion detected");
     }
  else  
           // Instruction des LEDs pas nécessaire, bien pratique pour connaître l'état précédent 
           // car LED reste allumée jusqu'à nouvelle détection
     {
           Serial.println("No motion");
     }
       
    
    
    
    }
*/
