#include "Arduino.h"
#include <Servo.h>
#include <LiquidCrystal.h>
#include <Password.h> 
#include <Keypad.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);
LiquidCrystal lcd(12,11,7,6,4,3); 
Servo servo;
int relaySolenoid = 2;
int PIR = 5;
int alarm = 10;
int buzzer = 13;
int led_rouge = 20;
int led_verte = 21;
int PIRvalue=0;
int pos=0;
int Turn = 0;
boolean Test = true;
char whichkey = "";
Password password = Password( "1234" );
const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
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
Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){

  Serial.begin(9600);
  SIM900.begin(19200);
  delay(2000);
  servo.attach(9); // pin servo D9
  pinMode(PIR, INPUT);
  pinMode(alarm, OUTPUT);
  digitalWrite(alarm, HIGH);//Alarm is declared once HIGH
  pinMode(led_rouge,OUTPUT);
  pinMode(led_verte,OUTPUT);
  pinMode(buzzer,OUTPUT);
  servo.write(50);
  delay (2000);
  lcd.begin(20,4);
  mykeypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  PIRvalue=digitalRead(PIR);
  int i;
  char whichkey = mykeypad.getKey();
  lcd.setCursor(0, 0);
  lcd.print("    Welcome");
  lcd.setCursor(0, 1);
  lcd.print(" Enter Password:");
   if(int(whichkey)!= 0){
    lcd.setCursor(16,1);
    lcd.print(" ");
    lcd.setCursor(16,1);
    }
    for(i=0;i<=Turn;++i){
      lcd.print("*");
      }
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (mykeypad.getState()){
    case PRESSED:
  Serial.print("Pressed: ");
  Serial.println(eKey);
  switch (eKey){
    case '*': checkPassword(); break;
    case '#': password.reset(); break;
    case 'A' && 'B' && 'C' && 'D':digitalWrite(relaySolenoid,LOW);
    default: password.append(eKey);
     }
  }
}
void checkPassword(){
  if (whichkey == password.evaluate()){
    Serial.println("Success");
    Serial.println("FUNCTION FOR OPEN THE DOOR");
    digitalWrite(relaySolenoid,HIGH);
    digitalWrite(led_verte, HIGH);
    digitalWrite(led_rouge, LOW);
    Test = true;
    Turn++;
    //Add code to run if it works
  }
  else{
    
    Serial.println("Wrong");
    digitalWrite(led_verte, LOW);
    digitalWrite(led_rouge, HIGH);
    sendSMS();
    Test = false;
    //add code to run if it did not work
  }
}


void sendSMS() {
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.println("AT + CMGS = \"+250783772950\"");
  delay(100);
  SIM900.println("Hey intruder detected ");
  Serial.println("Hey intruder detected ");
  delay(100);
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  delay(5000);//the time to send the message
}
