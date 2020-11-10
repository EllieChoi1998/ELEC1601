// Controls arduino car to automatically follow a line track using light sensors

#include <Servo.h> 

// initialize servo motors
Servo ServoLeft;
Servo ServoRight;

// define constants
const int RSensor = A0;  // analog input for right photoresistor
const int LSensor = A1;  // analog input for left photoresistor
const int light = 500;   // adjust this value based on ambient light in room
                         // pure white would be a low value, but can read higher in a darker room
// initialize value readings for sensors
int LSensorVal;
int RSensorVal;

// wheel speed constants
// can be adjusted for desired speed - about 90 is zero speed
int leftGo = 101;
int rightGo = 81;
int leftTurn = 96;
int rightTurn = 86;
int leftReverse = 86;
int rightReverse = 96;
int stopGo = 0;

void setup() 
{ 
  ServoLeft.attach(13);  // attach left servo to pin 13 on arduino
  ServoRight.attach(12); // attach right servo to pin 12 on arduino
  Serial.begin(9600);   // initialize serial
} 
 
void loop() 
{ 
 // read in sensor values from both photoresistors
 LSensorVal = analogRead(LSensor);
 RSensorVal = analogRead(RSensor);
 
  if (RSensorVal > light && LSensorVal > light) {  // sees no line on either side, goes straight until a line is seen
    //ServoLeft.write(leftGo);    // left wheel turns
    //ServoRight.write(rightGo);  // right wheel turns
    ServoLeft.write(stopGo);
    ServoRight.write(stopGo);
  } 
  else if (RSensorVal < light && LSensorVal > light) {  // sees line on right side, is making a right turn
    ServoLeft.write(leftTurn);      // left wheel turns
    ServoRight.write(rightReverse); // right wheel reverses
  } 
  else if (RSensorVal > light && LSensorVal < light) {  // sees line on left side, is making a left turn
    ServoLeft.write(leftReverse);  // left wheel reverses
    ServoRight.write(rightTurn);   // right wheel turns
  } 
  else {  // both are seeing line, goes straight until light is seen
    ServoLeft.write(leftTurn);    // left wheel turns
    ServoRight.write(rightTurn);  // right wheel turns
  }
  
  // for debugging
  Serial.print(LSensorVal);
  Serial.print(", ");
  Serial.println(RSensorVal);  
  
  delay(15);                           
}
