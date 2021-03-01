//This is a testing script for 2 biliage pump thrusters
// Author: James Taylor 
// Email: james.edmund.t@gmail.com

// Motor variables - up/down
int ENA = 8; // PWM control of motor speed
int m11 = 7; // motor 1 pin 1
int m12 = 6; // motor 1 pin 2
int m21 = 5; // motor 2 pin 1
int m22 = 4; // motor 2 pin 2

// Encoder varibles
const int swPin  = 37;
const int dtPin  = 33;
const int clkPin  = 31;

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
  middle = analogRead(Xpin);

  //Init Rotary
  pinMode(clkPin,INPUT);
  pinMode(dtPin,INPUT);
  pinMode(swPin,INPUT_PULLUP);
}

void loop() {
// simpletest(); // this is a simple motor test, motor go brrrrrrrrrrr
//X = analogRead(Ypin); // controls the speed of the motor
Y = analogRead(Xpin); // this value is not used, ignore
push = digitalRead(pushpin); // pressed = 0| unpressed = 1

readRotary();// the var "rotVal" contains a # from 1-10, will be used to 
motorspeed();

}



void readRotary( ) 
{ /* function readRotary */
  ////Test routine for Rotary
  // gestion position
  clkState = digitalRead(clkPin);
  if ((clkLast == LOW) && (clkState == HIGH)) {//rotary moving
//    Serial.print("Rotary position ");
    if (digitalRead(dtPin) == HIGH) {
      rotVal = rotVal - 1;
      if ( rotVal < 0 ) {
        rotVal = 0;
      }
    }
    else {
      rotVal++;
      if ( rotVal > 10 ) {
        rotVal = 10;
      }
    }
    //    Serial.println(rotVal);
    delay(200);
  }
  clkLast = clkState;

  //gestion bouton
  swState = digitalRead(swPin);
  if (swState == LOW && swLast == HIGH) {
    Serial.println("Rotary pressed");
    delay(100);//debounce
  }
  swLast = swState;
}

void motorspeed()
{
  int tol = 5; // tolerence of the joy stick
  // velcity = speed*direction aka how fast up or down
  int speed_downup = map(rotVal,0,10,60,250); // magnetude of velocity vector 
  
  if (middle+tol < Y)
  {
     up();
  }
  else if (middle-tol > Y)
  {
    down();
  }
}
// may need to switch down and up function 
void up()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  analogWrite(ENA, speed_downup);
}

void down()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  analogWrite(ENA, speed_downup);
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
