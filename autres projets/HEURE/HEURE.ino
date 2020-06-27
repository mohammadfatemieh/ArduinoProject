#include<Wire.h>
#include "Arduino.h"

#include "rtc_ds3231"
#include <LiquidCrystal.h>
LiquidCrystal lcd (8,9,4,5,6,7); 

#define BUFF_MAX 128

uint8_t time[8];
char recv[BUFF_MAX];
unsigned int recv_size = 0;
unsigned long prev, interval = 1000;



void setup() {
 Serial.begin(9600);
Wire.begin();
DS3231_init(DS3231_INTCN);
memset(recv, 0, BUFF_MAX);
Serial.println("GET time");
lcd.begin(16, 2);
lcd.clear();

Serial.println("Setting time");
parse_cmd("T305222511052019" , 16);

}

void loop() {
 

}
