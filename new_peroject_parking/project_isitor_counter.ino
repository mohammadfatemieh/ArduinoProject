#include <Servo.h>


#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
Servo myservoEntry;
Servo myservoExit;
//#define Entry 14
//#define Exit 19
//#define relay 2

int Entry_IR = 3;
int Exit_IR = 2;
int relay1 = 1;
int relay2 = 8;

int count = 0;
boolean roomFull = false;
boolean no_entry = false;
boolean nobody = false;
void ENTRY(){
  count++;
 delay(3000);
  
}
void EXIT(){
  
  
  
  
    count--;
  
  delay(2000);
 
  }



void setup() {
  myservoExit.attach(9);
  myservoEntry.attach(10);
  
//  myservoExit.write(90);
 // myservoEntry.write(90);
  lcd.begin(20,4);
  lcd.setCursor(4,0);
  lcd.print("Bidiractional ");
  lcd.setCursor(1,1);
  lcd.print("Visitor automatic");
  lcd.setCursor(1,2);
  lcd.print("Counter using Room");
  lcd.setCursor(2,3);
  lcd.print("Light controller");

  delay(4000);
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print("DONE BY");
  lcd.setCursor(6,1);
  lcd.print("THEOGENE");
  lcd.setCursor(9,2);
  lcd.print("AND");
  lcd.setCursor(6,3);
  lcd.print("IRENE");
  
  
  pinMode(Entry_IR, INPUT);
  pinMode(Exit_IR, INPUT);
 

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  
 delay(4000);

}

void loop() {

  int Entry_status = digitalRead(Entry_IR);
  int Exit_status = digitalRead(Exit_IR);
  // put your main code here, to run repeatedly:
  if(Entry_status == LOW){
    
    ENTRY();
    delay(1000);
    }
   /* if(Exit_status == LOW){
      if(count > 0){
       EXIT();
       myservoExit.write(0);
       delay(1000);
       myservoExit.write(90);
       //delay(1000);
      }
    }*/

    if(count <= 0){

      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
    //  myservoEntry.write(0);
      //delay(2000);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Nobody in room");
      lcd.setCursor(2,1);
      lcd.print("Entry  permitted");
      if(count == -1){
        count+=1;
        }
      lcd.setCursor(0,2);
      lcd.print("number of persons: ");
      //lcd.setCursor(9,2);
      lcd.print(count);
      delay(100);
      lcd.setCursor(3,3);
      lcd.print("Entry door open");
     // myservoEntry.write(100);
      
     
      
  }
  else if(count < 5){
    
     // myservoEntry.write(0);
      //delay(2000);
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Entry  permitted");
      lcd.setCursor(0,1);
      lcd.print("number of persons: ");
      //lcd.setCursor(9,1);
      lcd.print(count);
      
    //  myservoEntry.write(0);
      //delay(2000);
      delay(500);
      lcd.setCursor(3,3);
      lcd.print("Entry door open");
      
  }/*else if(count == 5){
    boolean roomFull = true;

    while( roomFull = true){
       digitalWrite(relay, HIGH);
     lcd.clear();
      lcd.setCursor(7,0);
      lcd.print("No Entry");
      lcd.setCursor(0,1);
      lcd.print("number of persons: ");
      //lcd.setCursor(9,1);
      lcd.print(count);
      myservoEntry.write(90);
      delay(200);
      roomFull = false; 
    }
     
  }*/
  else if(count == 5){
    lcd.clear();
    lcd.setCursor(6,1);
    lcd.print("Room full");
    lcd.setCursor(5,2);
    lcd.print("Please wait");
   delay(1000);
   Entry_status = digitalRead(Entry_IR);
  Exit_status = digitalRead(Exit_IR);
  delay(100);
 // myservoEntry.write(90);
  
  }
  else if(count == 0){
     digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
  }
 
}
