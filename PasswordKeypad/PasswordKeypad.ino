#include <LiquidCrystal.h> //include LCD library (standard library)
#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);
Password password_1 = Password( "1234" );
Password password_2 = Password( "5678" );

const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
byte pressTime = 0;
int countPress = 0;
int limitPress = 5; 
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 9,8,7,6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,3,2, };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print(" SYSTEM LOCKED ");
  lcd.setCursor(0, 2);
  lcd.print(" PRESS THE CODE ");
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	Serial.print("Pressed: ");
	Serial.println(eKey);
	switch (eKey){
	  case '*': checkPassword_1(); 
	            break;
    case'#': checkPassword_2();
             break;       
    case'A':password_1.reset();
            password_2.reset();
            pressTime = 0;
            break;        
	  default: password_1.append(eKey);
             password_2.append(eKey);
             pressTime++;     
     }
  }
}

void checkPassword_1(){
  if (password_1.evaluate()){
    lcd.setCursor(9,4);
    lcd.print(" ");
    lcd.setCursor(9,4);
    for(int i=0;i<=pressTime;i++){
      lcd.print("*");
      }
    lcd.clear();
    lcd.setCursor(0,2);
     lcd.print("  PROSSESSING...   ");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" SYSTEM UNLOCKED   ");
    delay(3000);
    lcd.clear();
     } 
  else{
     while(countPress < limitPress ){
    countPress +=1;
    lcd.setCursor(9,4);
    lcd.print(" ");
    lcd.setCursor(9,4);
    for(int i=0;i<=pressTime;i++){
      lcd.print("*");
      }
   Serial.println("INVALID CODE");
    lcd.clear();
    lcd.setCursor(0,2);
     lcd.print("  INVALID CODE");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" RETRY AGAIN   ");
    delay(3000);
    lcd.clear();
    if(countPress == limitPress ){
      
      }
    }
   }
}
void checkPassword_2(){
  if (password_2.evaluate()){
    lcd.setCursor(9,4);
    lcd.print(" ");
    lcd.setCursor(9,4);
    for(int i=0;i<=pressTime;i++){
      lcd.print("*");
      }
    lcd.clear();
    lcd.setCursor(0,2);
     lcd.print("  PROSSESSING...   ");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" SYSTEM LOCKED   ");
    delay(3000);
    lcd.clear();
     } 
  else{
    lcd.setCursor(9,4);
    lcd.print(" ");
    lcd.setCursor(9,4);
    for(int i=0;i<=pressTime;i++){
      lcd.print("*");
      }
   Serial.println("INVALID CODE");
    lcd.clear();
    lcd.setCursor(0,2);
     lcd.print("  INVALID CODE");
     delay(2000);
     lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print(" RETRY AGAIN   ");
    delay(3000);
    lcd.clear();
   }
}
