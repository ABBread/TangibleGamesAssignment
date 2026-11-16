#include <Servo.h>

enum galleryStates{
  STATE_IDLE,
  STATE_ACTIVE
};

Servo targetServo1;

Servo targetServo2;

Servo servoList = {targetServo1, targetServo2};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  targetServo1.attach(7);
  targetServo2.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:

}
