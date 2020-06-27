/*********
  Complete project details at http://randomnerdtutorials.com
*********/
#include <SoftwareSerial.h>
// Configure software serial port
SoftwareSerial SIM900(7, 8);

int PIR1= 5;
int PIR2= 6;
int PIR3= 11;
int PIR4= 12;
int led= 13;
int PIRvalue1=0;
int PIRvalue2=0;
int PIRvalue3=0;
int PIRvalue4=0;
void setup() {
  
  pinMode(PIR1, INPUT);
   pinMode(PIR2, INPUT);
   pinMode(PIR3, INPUT);
    pinMode(PIR4, INPUT);
   pinMode(led, OUTPUT);
 Serial.begin(9600);
  
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  // Give time to your GSM shield log on to network
  delay(20000);
  // Send the SMS
  sendSMS5();
}
void loop() {
 PIRvalue1=digitalRead(PIR1);
 PIRvalue2=digitalRead(PIR2);
 PIRvalue3=digitalRead(PIR3);
 PIRvalue4=digitalRead(PIR4);

 if (PIRvalue1== HIGH && PIRvalue2== LOW && PIRvalue3== LOW && PIRvalue4== LOW)
 {
  sendSMS1();
  
  }

 else if(PIRvalue1== LOW && PIRvalue2== HIGH && PIRvalue3== LOW && PIRvalue4== LOW)
 {
  sendSMS2();
  
  }
  else if(PIRvalue1== LOW && PIRvalue2== LOW && PIRvalue3== HIGH && PIRvalue4== LOW)
 {
  sendSMS3();
  
  }
  else if(PIRvalue1== LOW && PIRvalue2== LOW && PIRvalue3== LOW && PIRvalue4== HIGH)
 {
  sendSMS4();
  
  }

 
}
void sendSMS1() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+250780083122\"");
  delay(100);
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Detection in the saloon.");
  Serial.println("Detection in the saloon.");
  Serial.println("message sent");
  delay(100);
  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
}

/****************************************************************/


void sendSMS2() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+250780083122\"");
  delay(100);
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Detection in the saloon.");
  Serial.println("Detection in the saloon.");
  Serial.println("message sent");
  delay(100);
  //detection in room1
  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
}

/**********************************************************************/
void sendSMS3() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+250780083122\"");
  delay(100);
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Hey Detection in room1.");
  Serial.println("Hey Detection in room1.");
  Serial.println("message sent");
  delay(100);
  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
}

/*******************************************************************************/
void sendSMS4() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+250780083122\"");
  delay(100);
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Hey Detection in room2.");
  Serial.println("Hey Detection in room2.");
  Serial.println("message sent");
  delay(100);
  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
}

/************************************************************/

void sendSMS5() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+250780083122\"");
  delay(100);
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Hey system unlocked.");
  Serial.println("Hey system unlocked.");
  Serial.println("message sent");
  delay(100);
  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
}
