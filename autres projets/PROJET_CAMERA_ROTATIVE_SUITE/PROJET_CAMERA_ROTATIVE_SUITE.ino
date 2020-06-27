#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques)
Servo servo; //assigner l'objet "servo" comme servomoteur

int LED1 = 8 ;  //pins respectifs des LED
int LED2 = 10;

int PIR1 = 2;   //pins respectifs des capteurs PIR 
int PIR2 = 3;
int pos=0;
// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 

void setup()  {
     Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     pinMode(PIR1, INPUT);
     pinMode(PIR2, INPUT);
     
     pinMode(LED1, OUTPUT);
     pinMode(LED2, OUTPUT);
     digitalWrite(LED1, LOW);
       digitalWrite(LED2, LOW);
       
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
     for(int c = 0; c < 15; c++)// calibrer PIR jusqu'à 15 sec
     {  
           Serial.print(".");
           delay(500); 
     } 
     Serial.println ("PIR Ready to go!");
     servo.write(0); // bouger servo position initial 50 degrés  
} 

void loop()  {
  digitalWrite(LED1, LOW);
       digitalWrite(LED2, LOW);
     // les variables PIRvalue(bouléenne) stockent les inputs digitales (état) 
     // de leur PIR respectif soit H ou L
     PIRvalue1 = digitalRead(PIR1); 
     PIRvalue2 = digitalRead(PIR2);
    
     // Mouvement servo lors détection PIR1
     if(PIRvalue1 == LOW && PIRvalue2 == LOW)
{
   for (pos = 0,(PIRvalue1 == LOW && PIRvalue2 == LOW); pos <= 180; pos += 1) 
   {
     // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);  // waits 15ms for the servo to reach the position
    if(PIRvalue1 = digitalRead(PIR1), 
     PIRvalue2 = digitalRead(PIR2)) {pos=181;}
    
  }
  for (pos = 180,(PIRvalue1 == LOW && PIRvalue2 == LOW); pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); // waits 15ms for the servo to reach the position
    if(PIRvalue1 = digitalRead(PIR1), 
     PIRvalue2 = digitalRead(PIR2)) {pos=181;}
  }
  
  }
     else if (PIRvalue1 == HIGH && PIRvalue2 == LOW ) // && désigne le "et logique" bouléenne
     { 
           digitalWrite(LED1, HIGH);
           digitalWrite(LED2, LOW);
           
          
     
           servo.write(180);
           Serial.println("Position servo : PIR1, Motion detected");
     } 
     //Mouvement servo lors détection PIR2
     else if (PIRvalue1 == LOW && PIRvalue2 == HIGH) 
     { 
           digitalWrite(LED1, LOW);
           digitalWrite(LED2, HIGH);
          
          
           servo.write(90);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
    
     
     
     }  
