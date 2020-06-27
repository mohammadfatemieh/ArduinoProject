
#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
#include <LiquidCrystal.h>
int led=11;

LiquidCrystal lcd(12,11,7,6,4,3);



uRTCLib rtc;


void setup() {
  pinMode(led, OUTPUT);
delay (2000);
  lcd.begin(16,2);
  //lcd.clear();
  Serial.print("Serial OK");
 Serial.begin(9600);
  //  Max position: 32767

  #ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(0, 2); // D3 and D4 on ESP8266
  #else
    Wire.begin();
  #endif
  rtc.set_rtc_address(0x68);
  //rtc.set(0, 42, 13, 14, 3, 5, 19);
}

void loop() {
  rtc.refresh();

  lcd.setCursor(0,0);
  lcd.print("TIME :");
  lcd.print(rtc.hour());
  lcd.print(':');
  lcd.print(rtc.minute());
  lcd.print(':');
  lcd.print(rtc.second());

  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(rtc.temp());
  lcd.println();

  delay(3000);

  lcd.setCursor(0,1);
  lcd.print("DATE :");
  lcd.print(rtc.year());
  lcd.print('/');
  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.day());
  lcd.print("  ");

 delay(5000);



  digitalWrite( led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
  
  
}
