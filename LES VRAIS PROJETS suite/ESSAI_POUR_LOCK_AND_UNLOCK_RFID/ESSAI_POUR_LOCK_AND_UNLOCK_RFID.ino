#include <Servo.h> //inclure la bibliothèque du servomoteur (ses commandes spécifiques)
Servo servo; //assigner l'objet "servo" comme servomoteur


int PIR1 = 2;   //pins respectifs des capteurs PIR 
int PIR2 = 3;
int PIR3 = 4;
int PIR4 = 5;


// désigner les variables PIRvalue comme bouléenne 
// c'est à dire soit  TRUE ou HIGH (détection) soit FALSE ou LOW(non détection)
boolean PIRvalue1; 
boolean PIRvalue2; 
boolean PIRvalue3; 
boolean PIRvalue4; 
boolean togglestate= true;


void setup()  
{
     Serial.begin(9600); //interpeller le serial monitor pour afficher output sur serial monitor
     servo.attach(9); // pin servo D9
 
     
     pinMode(PIR2, INPUT);
     pinMode(PIR2, INPUT);
     pinMode(PIR3, INPUT);
     pinMode(PIR4, INPUT);
     
     
  
     //TARER - Temps pour PIRs de se (re)mettre en LOW, phase initiale
     Serial.print ("Setting PIR sensors ");
     Serial.println ("PIR Ready to go!");
     servo.write(0); // bouger servo position initial 50 degrés  
} 
int pos=0;
bool direct=false;
long prevTime=0;


void loop()  
{

    PIRvalue1 = digitalRead(PIR1);
    PIRvalue2 = digitalRead(PIR2);
    PIRvalue3 = digitalRead(PIR3);
    PIRvalue4 = digitalRead(PIR4); 

if (togglestate= true)

{

/************************************** SERVO MOTOR AND PIR SENSORS PART *******************************/
    if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == LOW)
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
    else if (PIRvalue1 == HIGH && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == LOW ) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(50);
    Serial.println("Position servo : PIR1, Motion detected");
} 
    else if (PIRvalue1 == LOW && PIRvalue2 == HIGH && PIRvalue3 == LOW && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
{ 
         
    servo.write(100);
    Serial.println("Position servo : PIR2, Motion detected");
} 
    else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == HIGH && PIRvalue4 == LOW) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(150);
    Serial.println("Position servo : PIR2, Motion detected");
}
    else if (PIRvalue1 == LOW && PIRvalue2 == LOW && PIRvalue3 == LOW && PIRvalue4 == HIGH) // && désigne le "et logique" bouléenne
{ 
    
    servo.write(160);
    Serial.println("Position servo : PIR2, Motion detected");
} 
    else if (PIRvalue1 == HIGH && PIRvalue2 == HIGH ) // && désigne le "et logique" bouléenne
{ 
    servo.write(90);
    Serial.println("Position servo : PIR2, Motion detected");
}
    else    
{
    Serial.println("No motion");
}    
}

/******************************* REAL TIME CLOCK PART *********************************************/












/********************************* REMOTE CONTROL PART *************************************************/










 }
