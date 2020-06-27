#include <Servo.h>


Servo myservo;
int pos = 0; 
int led=10;
int led2=11;
long prevMillis = 0;
int led_delay = 1000;
bool ledState = 0;


void setup() {
   myservo.attach(9); 
   pinMode(led, OUTPUT);
   pinMode(led2, OUTPUT);
   
  // put your setup code here, to run once:

}

void loop() {
  


  
  if (millis() - prevMillis> led_delay)
  {
    ledState !=ledState;
   digitalWrite(led2, ledState);
   prevMillis =millis();
   
   
    }


 digitalWrite(led, HIGH);
 delay(1000);
 digitalWrite(led, LOW);
 delay(1000);
 

}

/*#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
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
*/
