#include <IRremote.h>

const int RECV_PIN = 4;

const int redPin = 6;
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
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  
  }

  void loop()
  {
    if (irrecv.decode(&results))
    {
      switch(results.value)
      {
        
            case 0xFF12ED:
        if (togglestate1==0)
        {
          digitalWrite(redPin, HIGH);
          togglestate1=1;
          }
          else {
            digitalWrite(redPin, LOW);
            togglestate1=0;
            }
                   break;
            if (irrecv.decode(&results))

            {
              case 0xFF02FD:
        if (togglestate==0)
        {
          digitalWrite(yellowPin, HIGH);
          togglestate=1;
          }
          else {
            digitalWrite(yellowPin, LOW);
            togglestate=0;
            } 
              }
        
        
        break;
        

        
        }
        irrecv.resume();
      }
      
    }
