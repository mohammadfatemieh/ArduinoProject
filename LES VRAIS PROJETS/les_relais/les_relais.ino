#include<IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE=2;  //
IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);  //
int relay1 = 40;  //
int relay2 = 42;  //
int relay3 = 38;  //
int relay4 = 36;  //
int relay5 = 37;  //
int relay6 = 46;  //
int relay7 = 44;  //

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
       digitalWrite(relay2, HIGH);
       digitalWrite(relay3, HIGH);//
       digitalWrite(relay4, HIGH);  //
       digitalWrite(relay5, HIGH);  //
       digitalWrite(relay6, HIGH);  //
       digitalWrite(relay7, HIGH);  //
 

}

void loop() 
{
 if (monRecepteurInfraRouge.decode(&messageRecu))      //
   {
  
      if (messageRecu.value == 0x410807F)           //
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
         if (messageRecu.value == 0x41040BF)       //
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
         if (messageRecu.value == 0x410C03F)      //
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
         if (messageRecu.value == 0x41020DF)      //
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
         if (messageRecu.value == 0x410A05F)   //
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
         if (messageRecu.value == 0x41048B7)    //
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
         if (messageRecu.value == 0x410E01F)  //
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

    //delay(500);
    monRecepteurInfraRouge.resume();   //
  
  }
  delay(1);
}
