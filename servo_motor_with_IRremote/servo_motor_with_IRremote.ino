#include<IRremote.h>
#include<Servo.h>
#include <SPI.h> // RC522 Module uses SPI protocol
#include <MFRC522.h> // Library for Mifare RC522 Devices
const int RECV_PIN =11;
const int SERVO_PIN = 9;
int pos = 90;

#define RST_PIN 5
#define SS_PIN 53
MFRC522 module_rfid(SS_PIN, RST_PIN);// declaration of the module R
unsigned long lastCode;
IRrecv irrecv (RECV_PIN);
decode_results results;
Servo myservo;
void setup() {
  // put your setup code here, to run once:
irrecv.enableIRIn();
myservo.attach(SERVO_PIN);
myservo.write(pos);
}

void loop() {
  // put your main code here, to run repeatedly:
if(irrecv.decode(&results)){
  results.value=lastCode; 
  }
  if(results.value==0xFFFFFFFF){
    results.value=lastCode; 
    }
    if(results.value==0xFF02FD){
      lastCode = results.value;
      pos+=2;
      if(pos>180){
        
        pos=180;
      }
      myservo.write(pos);
      }
      if(results.value==0xFF12ED){
        lastCode= results.value;
        pos=90;
        myservo.write(pos);
        }
        delay(30);
        irrecv.resume();
}
