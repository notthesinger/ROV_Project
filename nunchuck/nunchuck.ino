#include <WiiChuck.h>

Accessory nunchuck;

void setup() {
  Serial.begin(115200);
  nunchuck_setup()
}

void loop() {
  nunchuck.readData();    // Read inputs and update maps
  Serial.print("Joy: ("); 
  Serial.print(nunchuck.getJoyX());
  Serial.print(", "); 
  Serial.print(nunchuck.getJoyY());
  Serial.println(")");

  Serial.print("Button: "); 
  if (nunchuck.getButtonZ()) Serial.print(" Z "); 
  if (nunchuck.getButtonC()) Serial.print(" C "); 

  Serial.println();
  delay(500);
}

void nunchuck_setup(){
  nunchuck.begin();
  if (nunchuck.type == Unknown) {
    nunchuck.type = NUNCHUCK;
  }
}
