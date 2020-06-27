/*********
  Complete project details at http://randomnerdtutorials.com
*********/
#include <SoftwareSerial.h>
// Configure software serial port
SoftwareSerial SIM900(7, 8);

int PIR= 5;
int led= 13;
int PIRvalue=0;
void setup() {
  pinMode(PIR, INPUT);
   pinMode(led, OUTPUT);
 Serial.begin(9600);
  
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // Give time to your GSM shield log on to network
  delay(2000);
  // Send the SMS
  
}
void loop() {
 PIRvalue=digitalRead(PIR);

 if (PIRvalue == HIGH)
 {
  sendSMS();
  //digitalWrite(led, HIGH);
  }
}
void sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+250780083122\"");
  delay(100);
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Detection in the saloon");
  Serial.println("Hey intruder detected in the saloon.");
  Serial.println("message sent");
  delay(100);
  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
}
