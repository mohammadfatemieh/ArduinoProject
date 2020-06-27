Here is the code: 

#include <Servo.h>

// author: jim demello feb 2014 //

// modified: Mar 31,2014 - added array to allow PIR to be used only once per HIGH state so it doesnt jump back

//                                    and forth between adjacent PIR servo positions.

boolean pirStatus;

Servo servo1; 

int servangle = 0; // servo angle variable

int pirNo[] = {3,4,5,6,7};          // pir pin numbers

int pirPrevLow[] = {1,1,1,1,1};     // previously low flag set to true

int pirPrevUsed[] = {0,0,0,0,0};   // track if PIR has been used after going HIGH

int pirPos[] = {10,60,100,140,170}; // positions for servo (0-180)

int curPosPir = 0;

int pirPin = 3;   

int ledPin = 13;

 

void setup(){

  Serial.begin(9600);

  servo1.attach(9); 

  for(int i=0;i<4;i++){

  pinMode(pirNo[i], INPUT);

   }

  pinMode(ledPin, OUTPUT);

  delay(10000); // calibrate for about 10 seconds

   }

////////////////////////////

//Main LOOP 

//////////////////

void loop(){

  for(int j=0;j<4;j++){ // for each PIR

     pirPin=pirNo[j];

     pirStatus = digitalRead(pirPin);

     if (pirStatus == HIGH) {

          digitalWrite(ledPin, HIGH);   // turn on led for kicks and to show PIRs are HIGH

          if(pirPrevLow[j])    {  

                if (curPosPir != pirPin && pirPrevUsed[j] == 0) { // if high PIR is different than current position PIR then move to new position

                   servo1.write(pirPos[j]);

                   curPosPir = pirPin; // keep current PIR 

                   pirPrevUsed[j] == 1;

                }

          pirPrevLow[j] = 0; // pir is now not low

          }

      } 

      else {

              digitalWrite(ledPin, LOW);  // turn off the led

              pirPrevLow[j] = 1;   // pir is now low

              pirPrevUsed[j] == 0;

      }

    } // end j number of pirs loop

  }// end infinite loop

 
