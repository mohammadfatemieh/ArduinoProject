/*This project was created by students of ULK year one Polytechnic Institute (ETT) 
 * including the help of HIRO,BARAKA AND MOSES , we are using the Light Depending Resistor (LDR)  
 * to control two LEDS . 
 *  some components used :
 *                   An Arduino UNO, 
 *                   One LED_RED, 
 *                   One Led_GREEN,
 *                   Three resisorts (One 1k reistor in serie with the photocell and 
 *                   Two  220 ohm resistors to protect the LEDS, 
 *                   A mini Breadboard,  
 *                   Some male to female and male to  male jumping  Wires
 */
// we are going to declare some variables and set them to the arduino 

int ldr = 2;//ldr set to pin 2 of the arduino
int led1 = 8;//led1 set to pin pin 8 of the arduino
int led2 = 9;// led2 set to pin 9 of the arduino

void setup() {
  // we are going to put our setup code here, to run once:
pinMode(2,INPUT); // define to pin 2 of the arduino as input
pinMode(8,OUTPUT);// define to pin 8 of the arduino as output
pinMode(9,OUTPUT);// define to pin 9 of the arduino as output
Serial.begin(9600);// This is the communication with the serialMonitor
}

void loop() {
  // we are going to put our main code here, to run repeatedly:
int sensorValue = digitalRead(ldr); // Arduino is going to read the sensorValue 
if (sensorValue >=700) // This condition is going to turn on the led1 when the sensorValue
                       // is greater or equal to 700  
{
  digitalWrite(led1,HIGH);//  Turn The led1 ON 
  digitalWrite(led2,LOW);// Turn The led2 is OFF
  
  }else if (sensorValue <= 500)// This condition is going to turn on the led1 when the sensorValue
                               // is less or equal to 500
  {
  digitalWrite(led1,LOW); // Turn the led1 OFF
  digitalWrite(led2,HIGH);// Turn the led2 ON
    }
    else // All the LEDS are going to be OFF 
    {
      digitalWrite(led1,LOW); // Turn the led1 OFF
      digitalWrite(led2,LOW);// Turn the led2 OFF
      
      }
    Serial.println(sensorValue);// We are going to read the sensorValue in SerialMonitor
}
