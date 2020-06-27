#include<IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE=4;
IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);

decode_results messageRecu;
int led1 =11;
int led2 =10;
int togglestate=0;
int togglestate1=0;
void setup() {
 Serial.begin(9600);
 monRecepteurInfraRouge.enableIRIn();
 monRecepteurInfraRouge.blink13(true);
 pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
 
 

}

void loop() {
 if (monRecepteurInfraRouge.decode(&messageRecu))

 {
  
  if (messageRecu.value == 0xFF02FD)
  {
  if(togglestate==0)
  {
     digitalWrite(led1, HIGH);
     togglestate=1;
    }
    else
    {
      digitalWrite(led1, LOW);
      togglestate=0;
      }
  }
  
  
   
        
         if (messageRecu.value == 0xFF12ED)
  {
    if(togglestate1==0)
   {
   digitalWrite(led2,HIGH);
   togglestate1=1;
        }
        else
        {
   digitalWrite(led2,LOW);
   togglestate1=0;
          }
        }

   
        
  
    delay(500);
    monRecepteurInfraRouge.resume();
  
  }
  delay(1);
}
