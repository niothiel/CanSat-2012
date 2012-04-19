#include <Servo.h>

#define SERVO_PIN 9

// Positions that we want the servos to be.
// It's #define'd for quick changing.
// Valid values are [0,180] inclusive.
#define POS1 0
#define POS2 180

Servo servo;

void initServo() {
  servo.attach(SERVO_PIN);
}

void servoPos1() {
  servo.write(POS1);
  delay(50);
}

void servoPos2() {
  servo.write(POS2);
  delay(50);
}


