#include <Servo.h>

enum galleryStates{
  STATE_IDLE,
  STATE_ACTIVE
};

Servo targetServo1, targetServo2;

int LDR1value, LDR2value;



void setup() {
  Serial.begin(9600);

  targetServo1.attach(7);
  targetServo2.attach(8);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  targetServo1.write(180);
  targetServo2.write(180);
}



void loop() {
  LDR1value = analogRead(A0);
  LDR2value = analogRead(A1);

  standeeManagement(LDR1value, targetServo1);
  standeeManagement(LDR2value, targetServo2);
}



void standeeManagement(int LDRvalue, Servo targetServo){
  bool servoFlippedUp;
  unsigned long timerStart;
  unsigned long timerDuration = random(1000, 5000);

  if (LDRvalue >= 900){
    if (!servoFlippedUp){
      timerStart = millis();
      targetServo.write(90);
      servoFlippedUp = true;
    }
    
  }

  if ((timerStart + timerDuration)<= millis()){
    targetServo.write(180);
    servoFlippedUp = false;
  }

}