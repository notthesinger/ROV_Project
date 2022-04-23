//##############encoder/LCD Code Initalization#########################
//###############################################################
//// IMPORT LIBRARIES
// LCD library(s)
#include <LiquidCrystal.h>
// IC2/Nunchuck library(s)
#include <Wire.h>
#include <WiiChuck.h>


// Create an LCD obj Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(22, 24, 26, 28, 30, 32);

// Rotary Encoder Inputs
//#define CLK 48
//#define DT 46
//#define SW 44

// Define address of multiplexer
Accessory nunchuck;
#define TCAADDR 0x70

//int counter = 0;
//int currentStateCLK;
//int lastStateCLK;
//int rot_val;
//unsigned long lastButtonPress = 0;
//###############################################################

// This helper function allows the communication on multiple IC2 ports, can use 1-7 IC2 devices
void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}


void setup() {
//  encoder_LCD_setup();
//  nunchuck_setup();
Serial.begin(115200);
  tcaselect(5);
  nunchuck.begin();
  if (nunchuck.type == Unknown) {
    nunchuck.type = NUNCHUCK;
  }
}

void loop() {
//  encoder(9);
//  LCDdisplayspeed();
  tcaselect(5);
  nunchuck.readData();    // Read inputs and update maps

  Serial.print("X: "); Serial.print(nunchuck.getAccelX());
  Serial.print(" \tY: "); Serial.print(nunchuck.getAccelY()); 
  Serial.print(" \tZ: "); Serial.println(nunchuck.getAccelZ()); 

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

//void nunchuck_setup()
//{
//  Serial.begin(115200);
//  tcaselect(6);
//  nunchuck.begin();
//  if (nunchuck.type == Unknown) {
//    nunchuck.type = NUNCHUCK;
//  }
//}
//void test_nunchuck(){
//  nunchuck.readData();    // Read inputs and update maps
//
//  Serial.print("X: "); Serial.print(nunchuck.getAccelX());
//  Serial.print(" \tY: "); Serial.print(nunchuck.getAccelY()); 
//  Serial.print(" \tZ: "); Serial.println(nunchuck.getAccelZ()); 
//
//  Serial.print("Joy: ("); 
//  Serial.print(nunchuck.getJoyX());
//  Serial.print(", "); 
//  Serial.print(nunchuck.getJoyY());
//  Serial.println(")");
//
//  Serial.print("Button: "); 
//  if (nunchuck.getButtonZ()) Serial.print(" Z "); 
//  if (nunchuck.getButtonC()) Serial.print(" C "); 
//
//  Serial.println();
//  delay(500);
//}

//void encoder_LCD_setup()
//{
//  //############# encoder/LCD Code Setup####################
//  //########################################################
//  // Set encoder pins as inputs
//  pinMode(CLK, INPUT);
//  pinMode(DT, INPUT);
//  pinMode(SW, INPUT_PULLUP);
//  // Setup Serial Monitor
////  Serial.begin(9600); //this can technically be 
//  // Read the initial state of CLK
//  lastStateCLK = digitalRead(CLK);
//  //LCD Screen display
//  // Specify the LCD's number of columns and rows. Change to (20, 4) for a 20x4
//  lcd.begin(16, 2);
//}
//void LCDdisplayspeed(){
//   
//  // Set the cursor on the third column and the first row, counting starts at 0:
//  lcd.setCursor(0, 0);
//  // Print the string 'Hello World!':
//  lcd.print("PW:");
//  // Set the cursor on the third column and the second row:
//  lcd.setCursor(3, 0);
//  // Print the string 'LCD tutorial':
//  lcd.print(counter);
//  lcd.noAutoscroll();
//  }


//int encoder(int max_val){
//  // Read the current state of CLK
//  currentStateCLK = digitalRead(CLK);
//  // If last and current state of CLK are different, then pulse occurred
//  // React to only 1 state change to avoid double count
//  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
//    // If the DT state is different than the CLK state then
//    // the encoder is rotating CCW so decrement
//    if (digitalRead(DT) != currentStateCLK) {
//      counter --;
//    } else {
//      // Encoder is rotating CW so increment
//      counter ++;
//    }
//    if (counter > max_val){
//      counter = max_val;
//    }
//    // no negative numbers 
//    if (counter < 0){
//      counter = 0;
//    }
//    Serial.print("Counter: ");
//    Serial.println(counter);
//  }
//  // Remember last CLK state
//  lastStateCLK = currentStateCLK;
//  // Read the button state
//  int btnState = digitalRead(SW);
//  //If we detect LOW signal, button is pressed
//  if (btnState == LOW) {
//    //if 50ms have passed since last LOW pulse, it means that the
//    //button has been pressed, released and pressed again
//    if (millis() - lastButtonPress > 50) {
//      Serial.println("Button pressed!");
//    }
//    // Remember last button press event
//    lastButtonPress = millis();
//  }
//  // Put in a slight delay to help debounce the reading
//  delay(1);
//  return counter;
//}
