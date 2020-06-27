#include <IRremote.h>

const int RECV_PIN = 4;

const int redPin = 13;
const int yellowPin = 7;


int togglestate = 0;
int togglestate1 = 0;


IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  irrecv.enableIRIn();
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  
  }

  void loop()
  {
    if (irrecv.decode(&results))
    {
      switch(results.value)
      {
        case 0xFFD827:
        digitalWrite(redPin, HIGH);
        delay(2000);
        digitalWrite(redPin, LOW);
        break;
        

        case 0xFF02FD:

        if(togglestate==0)

        {
          
          digitalWrite(yellowPin, HIGH);
          togglestate=1;
          
          }
          else {
            digitalWrite(yellowPin, LOW);
            togglestate=0;
            }
        break;
        }
        irrecv.resume();
      }
      
    }
