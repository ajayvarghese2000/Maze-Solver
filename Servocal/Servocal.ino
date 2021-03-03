#include <Servo.h> // Include servo library
Servo servoLeft; // Declare left servo signal
Servo servoRight; // Declare right servo signal
 
void setup() // Built in initialization block
{
  servoLeft.attach(10); // Attach left signal to pin 10
  servoRight.attach(11); // Attach left signal to pin 11
  servoLeft.writeMicroseconds(1500); // 1.5 ms stay still sig, pin 13
  servoRight.writeMicroseconds(1500); // 1.5 ms stay still sig, pin 12
}
void loop() // Main loop auto-repeats
{ // Empty, nothing needs repeating
}