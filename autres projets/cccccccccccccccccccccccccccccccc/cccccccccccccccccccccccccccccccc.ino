#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo; 
int pos = 0;    // variable to store the servo position
LiquidCrystal lcd(12,11,6,4,3,2);

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);

int buzzer = 8;
int led_rouge = 14;
int led_verte = 15;
int leed = 9;

bool togglestate = false;
void setup() {
  
  myservo.attach(9);  
 
  // put your setup code here, to run once:
  pinMode(led_rouge,OUTPUT);
  pinMode(led_verte,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(leed,OUTPUT);
  lcd.begin(20, 4);
  SPI.begin();
  module_rfid.PCD_Init();
  lcd.print("SYSTEM LOCKED ");
  lcd.setCursor(0, 1);
  lcd.print(" INDENTIFICATION");
  delay(3000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
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
     
     //servo();
    
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

/*void servo() {
  if (togglestate=true)
  {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  }
}*/

   
