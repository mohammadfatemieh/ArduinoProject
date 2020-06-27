#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,6,4,3,2);

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);
#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques)
Servo servo; //assigner l'objet "servo" comme servomoteur

int LED1 = 24 ;  //pins respectifs des LED
int LED2 = 25;
int led3 = 11;
int PIR1 = 8;   //pins respectifs des capteurs PIR 
int PIR2 = 7;

// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 
int buzzer = 24;
int led_rouge = 22;
int led_verte = 23;
int leed = 9;
int pos=0;
bool direct=false;
long prevTime=0;
int togglestate = 0;
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
        Serial.println ("PIR Ready to go!");
     servo.write(50); // bouger servo position initial 50 degrés  
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
    if(togglestate == 0){
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
     //delay(1000);
      digitalWrite(leed, HIGH);
      togglestate=1;
     lcd.clear();
     unlocked = true;
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
    
  else  
           // Instruction des LEDs pas nécessaire, bien pratique pour connaître l'état précédent 
           // car LED reste allumée jusqu'à nouvelle détection
     {
           Serial.println("No motion");
     }
  
     Serial.println("system unlocked ");
    }
   } /*else {
    Serial.println("invalid card");
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  ACCESS DENIED    ");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
   
     digitalWrite(led_rouge, LOW);
     
    
     lcd.clear();*/
   
  
  
  else {



Serial.println("barack");
//servomotor();
    
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
    if(togglestate == 0){
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
    
  else  
           // Instruction des LEDs pas nécessaire, bien pratique pour connaître l'état précédent 
           // car LED reste allumée jusqu'à nouvelle détection
     {
           Serial.println("No motion");
     }
  }
     Serial.println("system locked ");
   }
  }
  } else {
    Serial.println("invalid card");
   lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("  ACCESS DENIED    ");
     digitalWrite(led_rouge, HIGH);
     tone(buzzer, 200, 750);
     delay(2000);
   
     digitalWrite(led_rouge, LOW);
     
    
     lcd.clear();
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
}


   
