#include <Servo.h>

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);

int buzzer = 7;
int led_rouge = 14;
int led_verte = 15;

Servo Myservo;
void setup() {
   Myservo.attach(9);
  Myservo.write(90);
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);
  lcd.begin(16, 2);
  SPI.begin();
  module_rfid.PCD_Init();
  lcd.print("Dispositif");
  lcd.setCursor(0, 1);
  lcd.print("d'identification");
  delay(3000);
  lcd.clear();
 
}

void loop() {
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

  if (UID.substring(1) == "25 45 EE 7A") 
  {
    Myservo.write(0);
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
     
    
  }

  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCES REFUSE");
    digitalWrite(led_rouge, HIGH);
    tone(buzzer, 200, 750);
    delay(2000);
    digitalWrite(led_rouge, LOW);
    lcd.clear();
  }
}
