#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques)
Servo servo; //assigner l'objet "servo" comme servomoteur

int LED1 = 8 ;  //pins respectifs des LED
int LED2 = 10;
int LED3 = 11;
int LED4 = 12;
int LED5 = 13;
int PIR1 = 2;   //pins respectifs des capteurs PIR 
int PIR2 = 3;
int PIR3 = 4;
int PIR4 = 5;
int PIR5 = 6;
// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 
boolean PIRvalue3; 
boolean PIRvalue4; 
boolean PIRvalue5; 

void setup()  {
     Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     pinMode(PIR1, INPUT);
     pinMode(PIR2, INPUT);
     pinMode(PIR3, INPUT);
     pinMode(PIR4, INPUT);  
     pinMode(PIR5, INPUT);
     pinMode(LED1, OUTPUT);
     pinMode(LED2, OUTPUT);
     pinMode(LED3, OUTPUT);
     pinMode(LED4, OUTPUT);   
     pinMode(LED5, OUTPUT);   
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
     for(int c = 0; c < 15; c++)// calibrer PIR jusqu'à 15 sec
     {  
           Serial.print(".");
           delay(1000); 
     } 
     Serial.println ("PIR Ready to go!");
     servo.write(50); // bouger servo position initial 50 degrés  
} 

void loop()  {
     // les variables PIRvalue(bouléenne) stockent les inputs digitales (état) 
     // de leur PIR respectif soit H ou L
     PIRvalue1 = digitalRead(PIR1); 
     PIRvalue2 = digitalRead(PIR2);
     PIRvalue3 = digitalRead(PIR3);
     PIRvalue4 = digitalRead(PIR4);
     PIRvalue5 = digitalRead(PIR5);
     // Mouvement servo lors détection PIR1
     if (PIRvalue1 == HIGH && PIRvalue2 == LOW && PIRvalue3 == LOW && 
         PIRvalue4 == LOW && PIRvalue5 == LOW) // && désigne le "et logique" bouléenne
     { 
           digitalWrite(LED1, HIGH);
           digitalWrite(LED2, LOW);
           digitalWrite(LED3, LOW);
           digitalWrite(LED4, LOW);
           digitalWrite(LED5, LOW);
     
           servo.write(150);
           Serial.println("Position servo : PIR1, Motion detected");
     } 
     //Mouvement servo lors détection PIR2
     else if (PIRvalue1 == LOW && PIRvalue2 == HIGH && PIRvalue3 == LOW && 
                 PIRvalue4 == LOW && PIRvalue5 == LOW) 
     { 
           digitalWrite(LED1, LOW);
           digitalWrite(LED2, HIGH);
           digitalWrite(LED3, LOW);
           digitalWrite(LED4, LOW);
           digitalWrite(LED5, LOW);
     
           servo.write(130);
           Serial.println("Position servo : PIR2, Motion detected");
     } 
     //Mouvement servo lors détection PIR3
     else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == HIGH && 
                 PIRvalue4 == LOW && PIRvalue5 == LOW) 
     { 
           digitalWrite(LED1, LOW);
           digitalWrite(LED2, LOW);
           digitalWrite(LED3, HIGH);
           digitalWrite(LED4, LOW);
           digitalWrite(LED5, LOW);
     
           servo.write(90);
           Serial.println("Position servo : PIR3, Motion detected");
     } 
     //Mouvement servo lors détection PIR4
     else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && 
                 PIRvalue4 == HIGH && PIRvalue5 == LOW) 
     { 
           digitalWrite(LED1, LOW);
           digitalWrite(LED2, LOW);
           digitalWrite(LED3, LOW);
           digitalWrite(LED4, HIGH);
           digitalWrite(LED5, LOW);
     
           servo.write(40);
           Serial.println("Position servo : PIR4, Motion detected");
     } 
     //Mouvement servo lors détection PIR5
     else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && 
                 PIRvalue4 == LOW && PIRvalue5 == HIGH) 
     { 
           digitalWrite(LED1, LOW);
           digitalWrite(LED2, LOW);
           digitalWrite(LED3, LOW);
           digitalWrite(LED4, LOW);
           digitalWrite(LED5, HIGH);
     
           servo.write(8);
           Serial.println("Position servo : PIR5, Motion detected");
     } 
     // Si aucun des PIR ne détecte de mouvement
     else  
           // Instruction des LEDs pas nécessaire, bien pratique pour connaître l'état précédent 
           // car LED reste allumée jusqu'à nouvelle détection
     {
           Serial.println("No motion");
     }  
}
