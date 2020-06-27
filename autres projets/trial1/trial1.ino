#include <MFRC522.h>

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);
int led_verte=22;
int led2=23;
int buzzer=24;
bool unlocked = false;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  module_rfid.PCD_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
if(!unlocked) {
  if(readCard()){
    systemUnlocked();
    unlocked = true;
  }
}
else {
  if(readCard)unlocked = false;
  Serial.println("main function");
  delay(500);
}
}

bool readCard()
{
  Serial.println("reading card");
  String UID = "";
  //if (module_rfid.PICC_IsNewCardPresent() && module_rfid.PICC_ReadCardSerial()){
  Serial.println(module_rfid.uid.size);
    for (byte i= 0; i < module_rfid.uid.size; i++){
    
     UID.concat(String(module_rfid.uid.uidByte[i] < 0*10 ? " 0" : " "));
     UID.concat(String(module_rfid.uid.uidByte[i], HEX));
    }
     UID.toUpperCase();
     Serial.println();
   if (UID.substring(1) == "25 45 EE 7A" ) return true;
    //}
   return false;
}

void systemUnlocked()

{
    // lcd.clear();
     //lcd.setCursor(0, 0);
     
     
     //lcd.print(" SYSTEM UNLOCKED   ");
     Serial.println("System unlocked");
     digitalWrite(led_verte, HIGH);
     
     tone(buzzer, 1200, 100);
     delay(125);
     tone(buzzer, 1200, 100);
     delay(2000);
     digitalWrite(led_verte, LOW);
    // lcd.clear();
     //lcd.print("  PROSSESSING...   ");
     //delay(1000);
     // digitalWrite(leed, HIGH);
     // lcd.clear();
  
  }
