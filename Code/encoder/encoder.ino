//Rotary Encoder With LCD display


const int clk =  35;
const int data = 33;

const int maxencoderval = 8; // max value encoder can reach
 int testval;
 int counter = 0; 
 int State;
 int LastState;  
 
 void setup() { 
   pinMode (clk,INPUT);
   pinMode (data,INPUT);
   State = digitalRead(clk);   
   Serial.begin (9600); 
   LastState = digitalRead(clk);   
 } 
 void loop() { 
    testval = encoder_val();
    Serial.println(testval);
    delay(500);
 }

 int encoder_val(){
 
   if (State != LastState){     
     if (digitalRead(data) != State) { 
       counter ++;
     } else {
       counter --;
     }
     
     Serial.print("counter: ");
     Serial.println(counter);
     if (counter > maxencoderval){
      counter = 7; 
      }
   } 
   LastState = State; 
   return counter;
  }
