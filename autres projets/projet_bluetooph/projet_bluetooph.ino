int switch1=8;
int switch2=4;

int received=0;
int switch1_state=0;
int switch2_state=0;
    void setup()
    {
      Serial.begin(9600);
      pinMode(switch1, OUTPUT);
      pinMode(switch2, OUTPUT);

    }
    
    void loop() {
      if (Serial.available() >0);
      {
        char data = Serial.read();
        switch (data)
        {
           case'a': digitalWrite(8, HIGH); break;
           case'd': digitalWrite(8, LOW);break;
           default:break;
              }
            Serial.println(data);

                }
           delay(50);
        }
