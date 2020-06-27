// Include Software Serial library to communicate with GSM
#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;

// Configure software serial port
SoftwareSerial mySerial(10,2);

// Variable to store text message
String textMessage;

// Create a variable to store Lamp state
String lampState = "HIGH";
int relay = 13;

// Relay connected to pin 12
  

void setup() {
  // Set relay as OUTPUT
  pinMode(relay, OUTPUT);
  myservo.attach(9);  
  myservo.write(0);

  // By default the relay is off
  //digitalWrite(relay, HIGH);
  
  // Initializing serial commmunication
  Serial.begin(9600); 
  mySerial.begin(19200);

  // Give time to your GSM shield log on to network
  //delay(2000);
  Serial.print("mySerial ready...");

  // AT command to set SIM900 to SMS mode
 mySerial.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  mySerial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
 
  
}

void loop(){
  if(mySerial.available()>0){
    textMessage = mySerial.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  if(textMessage.indexOf("ON")>=0){
    // Turn on relay and save current state
    digitalWrite(relay,HIGH);
    lampState = "on";
    Serial.println("Relay set to ON");  
    textMessage = "";   
  }
    if(textMessage.indexOf("OFF")>=0){
    // Turn off relay and save current state
    digitalWrite(relay,LOW);
    lampState = "off"; 
    Serial.println("Relay set to OFF");
    textMessage = ""; 
  }
  if(textMessage.indexOf("STATE")>=0){
    String message = "Lamp is " + lampState;
    sendSMS(message);
    Serial.println("Lamp state resquest");
    textMessage = "";
  }
}  

// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  mySerial.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
    mySerial.println("AT+CMGS=\"+250785274184\""); 
  delay(100);
  // Send the SMS
  mySerial.println(message); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  mySerial.println((char)26); 
  delay(100);
  mySerial.println();
  // Give module time to send SMS
  delay(5000);  
}
