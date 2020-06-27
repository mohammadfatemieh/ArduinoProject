
#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,9,8,7,6,5,4,3,2);




uRTCLib rtc;



void setup() {
delay (2000);
lcd.begin(16,2);
  Serial.begin(9600);
  Serial.println("Serial OK");
    //Max position: 32767

  #ifdef ARDUINO_ARCH_ESP8266
    Wire.begin(0, 2); // D3 and D4 on ESP8266
  #else
    Wire.begin();
  #endif

  // Only used once, then disabled
   //rtc.set(30, 35, 14, 3, 15, 5, 19);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)

  rtc.set_rtc_address(0x68);

  
}

void loop() {
  rtc.refresh();
  Serial.print("RTC DateTime: ");
  lcd.setCursor(0,0);
  lcd.print(rtc.day());
  lcd.print('/');
  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.year());

  lcd.print(' ');
  lcd.setCursor(0,1);
  lcd.print(rtc.hour());
  lcd.print(':');
  lcd.print(rtc.minute());
  lcd.print(':');
  lcd.print(rtc.second());
  lcd.print(' ');
  lcd.setCursor(8,0);
  lcd.print(" DAY: ");
  lcd.print(rtc.dayOfWeek());
  lcd.setCursor(8,2);
  lcd.print(" Temp:");
  lcd.print(rtc.temp());

  lcd.println();

  //delay(1000);
}
