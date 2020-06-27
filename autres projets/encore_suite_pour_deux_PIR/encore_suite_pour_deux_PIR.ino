#include <Servo.h> 
Servo myservo;                               
//Servo library

int calibrationTime = 10;        



int pos = 0;
int pinPIRleft = 2;    
int pinLEDleft = 8;  
int pinPIRright = 4;
int pinLEDright = 10;
//the digital pin declaration for the  output for the various component 

//MAIN PROGRAM//

//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(pinPIRleft, INPUT);
  pinMode(pinLEDleft, OUTPUT);
  pinMode(pinPIRright, INPUT);
  pinMode(pinLEDright, OUTPUT);
  myservo.attach(9);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

//////////////////////////////LOOP
void loop(){
  
  if ((digitalRead(pinPIRleft) == HIGH) && (digitalRead(pinPIRright) == HIGH)) {
    digitalWrite(pinLEDright, HIGH);
    digitalWrite(pinLEDleft, HIGH);
    // do something here if both sensors detect movement. 
     myservo.write(myservo.read());
     delay(15);
     
  }
 
  if ((digitalRead(pinPIRleft) == LOW) && (digitalRead(pinPIRright) == LOW)) {
      digitalWrite(pinLEDleft, LOW);
      digitalWrite(pinLEDright, LOW);
    // do something here if both sensors detect no movement.
    myservo.write(myservo.read());
    delay(15); 
}

 if ((digitalRead(pinPIRleft) == HIGH) && (digitalRead(pinPIRright) == LOW)) {                           
    digitalWrite(pinLEDleft, HIGH);
    digitalWrite(pinLEDright,LOW); 
      if(pos>180){
      pos -= 1;      
      myservo.write(pos);                                        
      delay(15);
    } 

 }
 if ((digitalRead(pinPIRright) == HIGH)&& (digitalRead(pinPIRleft) == LOW)) {
    digitalWrite(pinLEDright, HIGH);
    digitalWrite(pinLEDleft, LOW);
      if(pos<0){
        pos += 1;
      myservo.write(pos);
      delay(15);
    }
}
 }
