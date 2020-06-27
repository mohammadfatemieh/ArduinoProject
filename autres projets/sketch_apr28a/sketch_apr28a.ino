int led=8;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(8, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  digitalWrite(8, LOW);  
  delay(1000);                     
  digitalWrite(LED_BUILTIN, HIGH);    
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);    
  
}
