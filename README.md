// Controls arduino car to automatically follow a line track using light sensors

#include <Servo.h> 

// initialize servo motors
Servo LeftServo;
Servo RightServo;

// define constants
const int RSensor = A0;  // analog input for right photoresistor
const int LSensor = A1;  // analog input for left photoresistor
const int light = 450;   // adjust this value based on ambient light in room
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

void setup() 
{ 
  LeftServo.attach(13);  // attach left servo to pin 6 on arduino
  RightServo.attach(12); // attach right servo to pin 9 on arduino
  Serial.begin(9600);   // initialize serial
} 
 
void loop() 
{ 
 // read in sensor values from both photoresistors
 LSensorVal = analogRead(LSensor);
 RSensorVal = analogRead(RSensor);
 
  if (RSensorVal > light && LSensorVal > light) {  // sees no line on either side, goes straight until a line is seen
    LeftServo.write(leftGo);    // left wheel turns
    RightServo.write(rightGo);  // right wheel turns
  } 
  else if (RSensorVal < light && LSensorVal > light) {  // sees line on right side, is making a right turn
    LeftServo.write(leftTurn);      // left wheel turns
    RightServo.write(rightReverse); // right wheel reverses
  } 
  else if (RSensorVal > light && LSensorVal < light) {  // sees line on left side, is making a left turn
    LeftServo.write(leftReverse);  // left wheel reverses
    RightServo.write(rightTurn);   // right wheel turns
  } 
  else {  // both are seeing line, goes straight until light is seen
    LeftServo.write(leftTurn);    // left wheel turns
    RightServo.write(rightTurn);  // right wheel turns
  }
  
  // for debugging
  Serial.print(LSensorVal);
  Serial.print(", ");
  Serial.println(RSensorVal);  
  
  delay(15);                           
}
