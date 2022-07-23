//##############encoder/LCD Code Initalization#########################
//###############################################################
//// IMPORT LIBRARIES
// LCD library(s)
//#include <LiquidCrystal.h>
#include "Adafruit_LiquidCrystal.h"
// IC2/Nunchuck library(s)
#include <Wire.h>
#include <WiiChuck.h>
// Temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>

// Create an LCD obj Parameters: (RS, E, D4, D5, D6, D7):
Adafruit_LiquidCrystal lcd(0);

// Define address of multiplexer
Accessory nunchuck1;
Accessory nunchuck2;

#define TCAADDR 0x70

// Sensor Variables
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float tempC;

// Control Variables
uint8_t vertical_thurster;
//###############################################################

// This helper function allows the communication on multiple IC2 ports, can use 1-7 IC2 devices
void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup() {
  Serial.begin(9600);
  sensors.begin();
  tcaselect(0);
  lcd.begin(16, 2);
  tcaselect(1);
  nunchuck1.begin();
  if (nunchuck1.type == Unknown) {
    nunchuck1.type = NUNCHUCK;
  }
}

void loop() {
  tcaselect(1);
  nunchuck1.readData();    // Read inputs and update maps
  vertical_thurster = nunchuck1.getJoyY();
  Serial.println(vertical_thurster);
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  //START LCD DISPLAY
  tcaselect(0);
  lcd.setCursor(0, 0);
  lcd.print("v:");
  // Set the cursor on the third column and the second row:
  lcd.setCursor(2, 0);
  // Print the string 'LCD tutorial':
  //  Serial.println(vertical_thurster);
  lcd.print(vertical_thurster);
  lcd.print("   ");
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.setCursor(2, 1);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.noAutoscroll();
  // BEGIN ERROR CATCHING  
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
}
