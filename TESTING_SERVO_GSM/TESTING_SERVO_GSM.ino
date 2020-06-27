#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo;

char inchar; // Will hold the incoming character from the GSM shield

SoftwareSerial SIM900(10, 2);
 
int led1 = 12; //Signal Indicator

void setup()
{
  Serial.begin(9600);
  // set up the digital pins to control

  servo.attach(9);  
  servo.write(0);
  //The servo is attached to pin 9
  /*pinMode(led1, OUTPUT);
 
  digitalWrite(led1, LOW); //Initiate the signal indicator

  // wake up the GSM shield
  SIM900power();
  SIM900.begin(19200);
  delay(2000);  // give time to log on to network.
  SIM900.print("AT+CMGF=1\r");  // set SMS mode to text
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  // blurt out contents of new SMS upon receipt to the GSM shield's serial out
  delay(100);
  Serial.println("GSM is now ready :)");*/
  
  // By default the relay is off
  //digitalWrite(relay, HIGH);
  
  // Initializing serial commmunication
  SIM900power();
  Serial.begin(9600); 
  SIM900.begin(19200);

  // Give time to your GSM shield log on to network
  //delay(2000);
  Serial.print("mySerial ready...");

  // AT command to set SIM900 to SMS mode
SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}
 
void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(7000);
}
 
void loop()
{
  //If a character comes in from the cellular module...
  if(SIM900.available() >0)
  {
    inchar=SIM900.read();
    if (inchar=='1')
    {
      delay(10);
 
      inchar=SIM900.read();
      if (inchar=='a')
      {
        delay(10);
        inchar=SIM900.read();
        if (inchar=='f') //If the sms received is "1af" ...
        {
          digitalWrite(led1, LOW); //To indicate that no signal is received.
        }
        else if (inchar=='o') //If the sms received is "1ao" ...
        {
          digitalWrite(led1, HIGH); //To indicate that signal is received.
         
          servo.write(0); //Turn servo to right.
          delay(1000);
          servo.write(30); //Turn servo to left.
          delay(1000);
          servo.write(90); //Face servo to the front.
          delay(1000);
 
        }
       
        delay(10);
       
          SIM900.println("AT+CMGD=1,4"); // delete all SMS
        }
      }
    }
 }
