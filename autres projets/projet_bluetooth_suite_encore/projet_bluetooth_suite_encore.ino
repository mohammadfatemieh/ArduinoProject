int ledblue=2;
int tx=1;
int rx=0;
char inSerial[15];

void setup() {
  Serial.begin(9600);
  pinMode(ledblue, OUTPUT );
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  allpinslow();
}

void loop() {
  int l=0;
  int m=0;
  delay(500);
  if (Serial.available()>o)
  {
    while (Serial.available ()>0)
    {
      inSerial[i]=Serial.read();
      i++;
      }
      inSerial[1]='\0';
    Check_Protocol(inSerial);
    }
    
}
void allpinslow()
{
  digitalWrite(ledblue, HIGH);
  digitalWrite(ledblue, LOW);
  }
 void Check_Protocol(char inStr[])
 {
  int i=0;
  int m=0;
  Serial.println(inStr);

  if (!strcmp(inStr,"2off))
  {
    allpinslow();
    digitalWrite(ledblue, LOW);
    Serial.println("Blue OFF");
    for(m=0; m<11; m++)
    {
      inStr[m]=0;
      i=0;
    }
     if (!strcmp(inStr, "2on"))
     {
      allpinslow();
      digitalWrite(ledblue, HIGH);
      Serial.println("Blue on");
      for(m=0; m++)
     }
      i=0;
      }

    else{
      for(m=0;m<11;m++)
      {
        inStr[m]=0;
        }
        i=0;
      }
    }
