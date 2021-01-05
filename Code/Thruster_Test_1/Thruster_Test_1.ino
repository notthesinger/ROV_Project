   //This is a testing script for 2 biliage pump thrusters
// Author: James Taylor 
// Email: james.edmund.t@gmail.com

// Motor variables
int ENA = 8; // PWM control of motor speed
int m11 = 7; // motor 1 pin 1
int m12 = 6; // motor 1 pin 2
int m21 = 5; // motor 2 pin 1
int m22 = 4; // motor 2 pin 2

// Controller variables
const int Ypin = A0;
const int Xpin = A1;
const int pushpin = 3;
// varibles to store joy stick values
int Y = 0;
int X = 0; // this is not needed as it is only up and down
int push = 0;
int middle = 0;
//int sp = 60; // This will control the speed of the motor, range of [60,250] 60 is the lowest the 500gph pump will spin
void setup() {
  // motor set up
  //set all moter pins to output
  analogWrite(ENA, 250);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  // controller set up
  Serial.begin(9600);
  pinMode(pushpin, INPUT_PULLUP);
  // find center of joy stick
  middle = analogRead(Ypin);
}

void loop() {
// simpletest(); // this is a simple motor test, motor go brrrrrrrrrrr
Y = analogRead(Ypin); // controls the speed of the motor
X = analogRead(Xpin); // this value is not used, ignore
push = digitalRead(pushpin); // pressed = 0| unpressed = 1

//print output of joy stick
Serial.print("\n Y = ");
Serial.print("\n");
Serial.print(Y);
Serial.print("\n Y norm = ");
Serial.print("\n");
Serial.print(calibrate(Y, middle));
delay(1000);
//Serial.print("\n pushpin = ");
//Serial.print("\n");
//Serial.println(push);
//  if (Y >= 60 &&  Y <=250){
//    speed_motor(Y);
//  }
//  else{
//      off();
//  }
}

int calibrate(int val, int middle){
  if (val < middle){
    return map(val, 0, middle, 0, -250);
  }
  else if  (val > middle){
    return map(val, middle, 1024, 0, 250);
  }
  else {
    return 0;    
    }
}

void off(){
  // This function will turn off the motor
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  analogWrite(ENA, 0);
}

void speed_motor(int s){
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  analogWrite(ENA, s);
  
  }

void simpletest(){
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(1000);
  }
