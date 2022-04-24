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
Accessory nunchuck1;
#define TCAADDR 0x70

//int counter = 0;
//int currentStateCLK;
//int lastStateCLK;
//int rot_val;
//unsigned long lastButtonPress = 0;

uint8_t vertical_thurster;
//###############################################################

// This helper function allows the communication on multiple IC2 ports, can use 1-7 IC2 devices
void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}




void nunchuck_setup()
{
  Serial.begin(115200);
  tcaselect(0);
  nunchuck1.begin();
  if (nunchuck1.type == Unknown) {
    nunchuck1.type = NUNCHUCK;
  }
//  vertical_thurster = nunchuck1.getJoyY();
}

void thruster_controls(){
  // Vertical thrusters  
//  tcaselect();
  nunchuck1.readData();    // Read inputs and update maps
  vertical_thurster = nunchuck1.getJoyY();
  delay(10);
}

void LCD_setup()
{
  // Specify the LCD's number of columns and rows. Change to (20, 4) for a 20x4
  lcd.begin(16, 2);
}
void LCDdisplaycontrols(){
   
  // Set the cursor on the third column and the first row, counting starts at 0:
  lcd.setCursor(0, 0);
  // Print the string 'Hello World!':
  lcd.print("vertical:");
  // Set the cursor on the third column and the second row:
  lcd.setCursor(9, 0);
  // Print the string 'LCD tutorial':
  Serial.println(vertical_thurster);
  lcd.print(vertical_thurster);
  lcd.print("   ");
  lcd.noAutoscroll();
  }

void setup() {
  LCD_setup();
  nunchuck_setup();
}

void loop() {
  thruster_controls();
  LCDdisplaycontrols();
}
