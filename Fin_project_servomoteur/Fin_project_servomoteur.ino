#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques)
Servo servo; //assigner l'objet "servo" comme servomoteur

int LED1 = 24 ;  //pins respectifs des LED
int LED2 = 25;
int led3 = 11;
int PIR1 = 22;   //pins respectifs des capteurs PIR 
int PIR2 = 26;

// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 


void setup()  
{
     Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     pinMode(PIR1, INPUT);
     pinMode(PIR2, INPUT);
     pinMode(led3, OUTPUT);
     pinMode(LED1, OUTPUT);
     pinMode(LED2, OUTPUT);
  
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
        Serial.println ("PIR Ready to go!");
     servo.write(50); // bouger servo position initial 50 degrés  
} 
int pos=0;
bool direct=false;
long prevTime=0;
void loop()  
{digitalWrite(led3, HIGH);
           
            
   PIRvalue1 = digitalRead(PIR1); 
     PIRvalue2 = digitalRead(PIR2);
   if (PIRvalue1 == LOW && PIRvalue2 == LOW)
      {
  if((millis()-prevTime)>=15)
  {
    prevTime=millis();
  if(pos==180)direct=true;
  if(pos==0)direct=false;
  if(direct)pos--;
  else pos++;
  servo.write(pos); 
  }
      }

else if (PIRvalue1 == HIGH && PIRvalue2 == LOW ) // && désigne le "et logique" bouléenne
      { 
           digitalWrite(LED1, HIGH);
           digitalWrite(LED2, LOW);
           
           servo.write(180);
           Serial.println("Position servo : PIR1, Motion detected");
      } 
  else if (PIRvalue1 == LOW && PIRvalue2 == HIGH ) // && désigne le "et logique" bouléenne
     { 
           digitalWrite(LED1, LOW);
           digitalWrite(LED2, HIGH);
           
           servo.write(90);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
    
  else  
           // Instruction des LEDs pas nécessaire, bien pratique pour connaître l'état précédent 
           // car LED reste allumée jusqu'à nouvelle détection
     {
           Serial.println("No motion");
     }
      
}
