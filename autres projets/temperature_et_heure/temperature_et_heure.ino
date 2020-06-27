
#include "Arduino.h"
#include "Wire.h"
#include "uRTCLib.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(5,4,3,2,11,12);



uint8_t time[9];

unsigned int recv_size = 0;
unsigned long prev, interval = 1000;

uRTCLib rtc;


void setup() {
delay (2000);
	Serial.begin(9600);
  Wire.begin();

  
	Serial.println("Serial OK");
	//  Max position: 32767
lcd.begin(16, 2);
lcd.clear();

Serial.println("setting time");
parse_cmd("setting time");
parse_cmd("T305222511052019");
	#ifdef ARDUINO_ARCH_ESP8266
		Wire.begin(0, 2); // D3 and D4 on ESP8266
	#else
		Wire.begin();
	#endif

	// Only used once, then disabled
	//  rtc.set(0, 42, 16, 6, 2, 5, 15);
	//  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)

	rtc.set_rtc_address(0x68);
}

void loop() {
	rtc.refresh();
	Serial.print("RTC DateTime: ");

	Serial.print(rtc.year());
	Serial.print('/');
	Serial.print(rtc.month());
	Serial.print('/');
	Serial.print(rtc.day());

	Serial.print(' ');

	Serial.print(rtc.hour());
	Serial.print(':');
	Serial.print(rtc.minute());
	Serial.print(':');
	Serial.print(rtc.second());

	Serial.print(" DOW: ");
	Serial.print(rtc.dayOfWeek());

	Serial.print(" - Temp: ");
	Serial.print(rtc.temp());

	Serial.println();

	delay(1000);
}
