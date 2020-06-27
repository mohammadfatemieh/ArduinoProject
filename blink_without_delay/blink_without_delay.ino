

int led1= 13;
int led2 = 12;
const unsigned long blink_interval1= 2000;
const unsigned long blink_interval2= 500;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
task_led1();
task_led2();
}


void task_led1()

{
  static unsigned long previousMillisLed1 = 0;
  static byte stateled1= LOW;
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillisLed1 >= blink_interval1)

   {
   previousMillisLed1 =  currentMillis;
    stateled1 = ! stateled1;
    digitalWrite(led1, stateled1);
    }
  
  }

  void task_led2()

{
  static unsigned long previousMillisLed2 = 0;
  static byte stateled2= LOW;
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillisLed2 >= blink_interval2)

   {
   previousMillisLed2 =  currentMillis;
    stateled2 = ! stateled2;
    digitalWrite(led2, stateled2);
    }
  
  }
