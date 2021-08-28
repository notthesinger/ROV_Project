//##############encoder/LCD Code Initalization#########################
//###############################################################
// LCD stuff
#include <LiquidCrystal.h>
// Create an LCD obj Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(22, 24, 26, 28, 30, 32);

// Rotary Encoder Inputs
#define CLK 48
#define DT 46
#define SW 44

int counter = 0;
int currentStateCLK;
int lastStateCLK;
int rot_val;
unsigned long lastButtonPress = 0;
//###############################################################

void setup() {
  encoder_LCD_setup();
}

void loop() {
  encoder(9);
  LCDdisplayspeed();
}

void encoder_LCD_setup()
{
  //############# encoder/LCD Code Setup####################
  //########################################################
  // Set encoder pins as inputs
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);
  // Setup Serial Monitor
  Serial.begin(9600); //this can technically be 
  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
  //LCD Screen display
  // Specify the LCD's number of columns and rows. Change to (20, 4) for a 20x4
  lcd.begin(16, 2);
}
void LCDdisplayspeed(){
   
  // Set the cursor on the third column and the first row, counting starts at 0:
  lcd.setCursor(0, 0);
  // Print the string 'Hello World!':
  lcd.print("PW:");
  // Set the cursor on the third column and the second row:
  lcd.setCursor(3, 0);
  // Print the string 'LCD tutorial':
  lcd.print(counter);
  lcd.noAutoscroll();
  }


int encoder(int max_val){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);
  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter --;
    } else {
      // Encoder is rotating CW so increment
      counter ++;
    }
    if (counter > max_val){
      counter = max_val;
    }
    // no negative numbers 
    if (counter < 0){
      counter = 0;
    }
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
  // Read the button state
  int btnState = digitalRead(SW);
  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
    }
    // Remember last button press event
    lastButtonPress = millis();
  }
  // Put in a slight delay to help debounce the reading
  delay(1);
  return counter;
}
