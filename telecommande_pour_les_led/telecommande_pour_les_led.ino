// Include IR Remote Library by ken shirriff
#include<IRremote.h>

//  define sensor pin
const int RECV_PIN = 11;

// define LED pin constants
int ledyellow = 5;
int ledred = 13;
// define integer to remember toggle state 

int togglestate = 0;

// define IR Receiver and results objects

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // enable the IR receiver 
  irrecv.enableIRIn();

  // set LED pins as OUTPUT

  pinMode(ledyellow, OUTPUT);
  pinMode(ledred, OUTPUT);

}

void loop() {
if (irrecv.decode(&results))
{
  switch(results.value)
  {
    case 0x4104887:    
    digitalWrite(ledyellow, HIGH);
    delay(2000);
   // digitalWrite(ledyellow, LOW);
    break;
    
      case 0x41048B7:
    if (togglestate==0)
    {
      digitalWrite(ledred,HIGH);
      togglestate=1;
      }
    else{
      digitalWrite(ledred,LOW);
      togglestate=0;
      }
      break;
    }
    }
  irrecv.resume();
  } 
