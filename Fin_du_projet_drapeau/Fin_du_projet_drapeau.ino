int switch1 = 8 ;
int switch2 = 4;
int i;

void setup()
{
  Serial.begin(9600);
  pinMode(switch1, OUTPUT);
pinMode(switch2, OUTPUT);
  digitalWrite(8,HIGH );
  digitalWrite(4, HIGH);
}

void loop() {

  if (Serial.available() > 0);
  {
    char data = Serial.read();
    switch (data)
    { 
      case'a':
          for (i=0;i<10,data!='e';i++)
         { 
            digitalWrite(8,LOW);
            digitalWrite(4,HIGH);
            delay(3000);
            digitalWrite(8,HIGH);
            digitalWrite(4,HIGH);
            delay(3000);
            if(data = Serial.read()) {i='e';}
          } 
      break;
      case'e':
        digitalWrite (8, HIGH);break;
        digitalWrite (4, HIGH);break;
        case 'd': 
        for( i=0; i<10, data!='h'; i++)
        {
          digitalWrite(4,LOW);
          digitalWrite(8,HIGH);
            delay(3000);
            digitalWrite(4,HIGH);
            digitalWrite(8,HIGH);
            delay(3000);
            if(data = Serial.read()) {i='h';}
          }break;
        case 'h': 
        digitalWrite(4, HIGH);break;
        digitalWrite(8, HIGH);break;
      
      default: break;
    }
    Serial.println(data);

  }
  delay(50);
}
