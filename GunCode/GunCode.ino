
enum gunStates{
  STATE_IDLE,
  STATE_READY,
  STATE_FIRING,
  
};

gunStates activeState = STATE_IDLE;

int ammo = 10;

unsigned long startTime;
unsigned long shotTime = 500;

bool shotFired = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(8, INPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println(startTime);
  
  if(digitalRead(8) == 1){
    activeState = STATE_FIRING;
  }
  else{
    activeState = STATE_IDLE;
  }
  
  if(activeState == STATE_FIRING){
    if(ammo >= 0){
      if(!shotFired)
      {
        startTime = millis();
        ammo -= 1;
        shotFired = true;
      }
      else{
        if (millis() < (startTime + shotTime)){
          digitalWrite(7, HIGH);
        }
        else{
          digitalWrite(7, LOW);
        }
      }
    }
  }
  else{
    shotFired = false;
    digitalWrite(7, LOW);
  }
}
