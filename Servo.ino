#define SERVO_PIN 10

// Positions that we want the servos to be.
// It's #define'd for quick changing.
// Valid values are [0,180] inclusive.
#define SERVO_OPEN_POS 5
#define SERVO_CLOSED_POS 175

Servo servo;

void initServo() {
  servo.attach(SERVO_PIN);
}

void servoOpen() {
  servo.write(SERVO_OPEN_POS);
  delay(50);
}

void servoClose() {
  servo.write(SERVO_CLOSED_POS);
  delay(50);
}


