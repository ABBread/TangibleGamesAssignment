#include <Servo.h>

enum galleryStates{
  STATE_IDLE,
  STATE_ACTIVE
};

Servo targetServo1, targetServo2;

int LDR1value, LDR2value;

bool servoFlippedDown1, servoFlippedDown2 = false;
unsigned long timerStart1, timerStart2;
unsigned long timerDuration1, timerDuration2 = 3000;


void setup() {
  Serial.begin(9600);

  targetServo1.attach(7);
  targetServo2.attach(8);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  targetServo1.write(90);
  targetServo2.write(90);
}



void loop() {
  Serial.println(LDR1value);

  LDR1value = analogRead(A0);
  LDR2value = analogRead(A1);

  standeeManagement(LDR1value, targetServo1, servoFlippedDown1, timerStart1, timerDuration1);
  standeeManagement(LDR2value, targetServo2, servoFlippedDown2, timerStart2, timerDuration2);
}



void standeeManagement(int LDRvalue, Servo targetServo, bool& servoFlippedDown, unsigned long& timerStart, unsigned long& timerDuration){

  if (LDRvalue >= 900){
    if (!servoFlippedDown){
      timerStart = millis();
      targetServo.write(180);
      timerDuration = random(5000);
      servoFlippedDown = true;
    }
    
  }

  if ((timerStart + timerDuration)<= millis()){
    targetServo.write(90);
    servoFlippedDown = false;
  }

}