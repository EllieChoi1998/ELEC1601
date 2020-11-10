#include <Servo.h> 

// initialize servo motors
Servo ServoLeft;
Servo ServoRight;

int leftGo = 1700;
int rightGo = 1300;
int leftTurn = 96;
int rightTurn = 86;
int leftReverse = 86;
int rightReverse = 96;
int stopGo = 0;


void setup()
{
  pinMode(10, INPUT); pinMode(9, OUTPUT); // Left IR & Receiver
  pinMode(3, INPUT); pinMode(2, OUTPUT); // Right IR & Receiver
  ServoLeft.attach(13);
  ServoRight.attach(12);
  Serial.begin(9600);
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  

void loop(){
  int irLeft = irDetect(9, 10, 38000);       // Check for object
  int irRight = irDetect(2, 3, 38000);       // Check for object

  Serial.print("left: ");
  Serial.print(irLeft);
  Serial.print(" Right: ");
  Serial.print(irRight);
  Serial.print("\n");

  if(irRight == 0 && irLeft == 0){
    ServoLeft.write(leftGo);
    ServoRight.write(rightGo);    
  } 
  else if (irRight == 1 && irLeft == 0){
    ServoLeft.write(leftTurn);
    ServoRight.write(rightReverse);
  }
  else if (irRight == 0 && irLeft == 1){
    ServoLeft.write(leftReverse);
    ServoRight.write(rightTurn);
  }
}
