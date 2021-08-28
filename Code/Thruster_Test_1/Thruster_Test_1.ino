//This is a testing script for 2 biliage pump thrusters
// Author: James Taylor 
// Email: james.edmund.t@gmail.com

//##############encoder/LCD Code Initalization#########################
//###############################################################
// LCD stuff
#include <LiquidCrystal.h>
// Create an LCD object. Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(22, 24, 26, 28, 30, 32);

// Rotary Encoder Inputs
#define CLK 48
#define DT 46
#define SW 44
// Variables used in 
int counter = 0;
int currentStateCLK;
int lastStateCLK;
int rot_val;
unsigned long lastButtonPress = 0;

//##############up/down thruster#########################
//###############################################################
// Motor variables - up/down
int ENA1 = 8; // PWM control of motor one speed
int m11 = 7; // motor 1 pin 1
int m12 = 6; // motor 1 pin 2
int m21 = 5; // motor 2 pin 1
int m22 = 4; // motor 2 pin 2

// Encoder varibles
const int swPin  = 37;
const int dtPin  = 33;
const int clkPin  = 31;
int rotvalget = 0;

int rotVal  = 0;
bool clkState  = LOW;
bool clkLast  = HIGH;
bool swState  = HIGH;
bool swLast  = HIGH;

// Controller variables
const int Ypin = A0;
const int Xpin = A1;
const int pushpin = 3;
// varibles to store joy stick values
int Y = 0;
int X = 0; // this is not needed as it is only up and down
int push = 0;
int middle = 0; // center value for joy stick controller 
int sp = 80; // This will control the speed of the motor, range of [60,250] 60 is the lowest the 500gph pump will spin


void setup() {
  // controller set up
  Serial.begin(9600);
  up_down_thruster_setup();
  encoder_LCD_setup();
}

void loop() {
// simpletest(); // this is a simple motor test, motor go brrrrrrrrrrr
//X = analogRead(Ypin); // controls the speed of the motor
//push = digitalRead(pushpin); // pressed = 0| unpressed = 1
Y = analogRead(Xpin); 
//Serial.println("\n\nEncoder values: ");
rotvalget = encoder(9);
//Serial.println(rotvalget);
delay(500);
motorspeed(rotvalget, Y, middle);
}

void encoder_LCD_setup()
{
  // Set encoder pins as inputs
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
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
    LCDdisplayspeed();
//    rotvalget = counter;
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

void up_down_thruster_setup(){
   // motor set up
  //set all moter pins to output
  analogWrite(ENA1, 250);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(pushpin, INPUT_PULLUP);
  // find center of joy stick
  middle = analogRead(Xpin);
  //Init Rotary
  pinMode(clkPin,INPUT);
  pinMode(dtPin,INPUT);
  pinMode(swPin,INPUT_PULLUP);
}


void motorspeed(int rotvalget,int readval,int mid)
{
  int tol = 20; // tolerence of the joy stick
  // velcity = speed*direction aka how fast up or down
  int speed_downup = map(rotvalget,0,9,0,250); // magnetude of velocity vector 
  Serial.println("\n Proposed speed value:");
  Serial.println(speed_downup);
  if (middle+tol < readval)
  {
//     up(speed_downup);
     Serial.println("DIVE, DIVE!!!!!");
  }
  else if (mid-tol > readval)
  {
//    down(speed_downup);
      Serial.println("SURFACE, SURFACE!!!!!");
  }
}
// may need to switch down and up function 
void up(int sdu)
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  analogWrite(ENA1, sdu);
  Serial.println("\nSpeed for up is:");
  Serial.println(sdu);
  delay(1000);
}

void down(int sdu)
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  analogWrite(ENA1, sdu);
  Serial.println("\nSpeed for down is:");
  Serial.println(sdu);
  delay(1000);
}
void off(){
  // This function will turn off the motor
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  analogWrite(ENA1, 0);
  Serial.println("\n Motor is off");
  delay(1000);
}

void speed_motor(int s){
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  analogWrite(ENA1, s);
  
  }

void simpletest(){
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(1000);
  }
