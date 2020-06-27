#include<IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE=4;  //
IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);  //
int relay1 = 1;  //
int relay2 = 2;  //
int relay3 = 3;  //
int relay4 = 4;  //
int relay5 = 5;  //
int relay6 = 6;  //
int relay7 = 7;  //

decode_results messageRecu;  //
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------

        int togglestate1=0;  //
        int togglestate2=0;  //
        int togglestate3=0;  //
        int togglestate4=0;  //
        int togglestate5=0;  //
        int togglestate6=0;  //
        int togglestate7=0;  //
//----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
void setup() 
{
        Serial.begin(9600);  //
        monRecepteurInfraRouge.enableIRIn();  //
        monRecepteurInfraRouge.blink13(true);  //
        pinMode(relay1, OUTPUT);  //
        pinMode(relay2, OUTPUT);  //
        pinMode(relay3, OUTPUT);  //
        pinMode(relay4, OUTPUT);  //
        pinMode(relay5, OUTPUT);  //
        pinMode(relay6, OUTPUT);  //
        pinMode(relay7, OUTPUT);  //

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
       digitalWrite(relay1, HIGH);  //
       digitalWrite(relay2, HIGH);  //
       digitalWrite(relay4, HIGH);  //
       digitalWrite(relay5, HIGH);  //
       digitalWrite(relay6, HIGH);  //
       digitalWrite(relay7, HIGH);  //
 

}

void loop() 
{
 if (monRecepteurInfraRouge.decode(&messageRecu))      //
   {
  
      if (messageRecu.value == 0xFF02FD)           //
        {
           if(togglestate1==0)                   //
        {
          digitalWrite(relay1, LOW);           //
          togglestate1=1;                      //
        }
      else
        {
          digitalWrite(relay1, HIGH);  //
          togglestate1=0;  //
        }
        }
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)       //
        {
         if(togglestate2==0)                   //
        {
         digitalWrite(relay2,LOW);           //
         togglestate2=1;                    //
        }
        else
        {
        digitalWrite(relay2,HIGH);      //
        togglestate2=0;                //
        }
        }
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)      //
        {
         if(togglestate3==0)                  //
        {
         digitalWrite(relay3,LOW);         //
         togglestate3=1;                  //
        }
        else
        {
        digitalWrite(relay3,HIGH);  //
        togglestate3=0;  //
        }
        }
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)      //
        {
         if(togglestate4==0)                   //
        {
         digitalWrite(relay4,LOW);           //
         togglestate4=1;                   //
        }
        else
        {
        digitalWrite(relay4,HIGH);    //
        togglestate4=0;              //
        }
        }
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)   //
        {
         if(togglestate5==0)                 //
        {
         digitalWrite(relay5,LOW);          //
         togglestate5=1;                   //
        }
        else
        {
        digitalWrite(relay5,HIGH);       //
        togglestate5=0;                 //
        }
        }
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)    //
        {
         if(togglestate6==0)                 //
        {
         digitalWrite(relay6,LOW);         //
         togglestate6=1;                  //
        } 
        else
        {
        digitalWrite(relay6,HIGH);    //
        togglestate6=0;              //
        }
        }
//----------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
         if (messageRecu.value == 0xFF12ED)  //
        {
         if(togglestate7==0)              //
        {
         digitalWrite(relay7,LOW);      //
         togglestate7=1;              //
        }
        else
        {
        digitalWrite(relay7,HIGH); //
        togglestate7=0;          //
        }
        }
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------

    delay(500);
    monRecepteurInfraRouge.resume();   //
  
  }
  delay(1);
}
