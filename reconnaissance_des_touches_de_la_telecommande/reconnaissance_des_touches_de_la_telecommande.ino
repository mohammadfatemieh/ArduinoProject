#include<IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE=11;
IRrecv monRecepteurInfraRouge(DIN_RECEPTEUR_INFRAROUGE);

decode_results messageRecu;

void setup() {
 Serial.begin(9600);
 monRecepteurInfraRouge.enableIRIn();
 monRecepteurInfraRouge.blink13(true);

}

void loop() {
  // put your main code here, to run repeatedly:
if (monRecepteurInfraRouge.decode(&messageRecu)) 

{
  Serial.println(messageRecu.value, HEX);
  delay(500);
  monRecepteurInfraRouge.resume();
  }
  delay(1);
}
