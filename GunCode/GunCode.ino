
enum gunStates{
  STATE_IDLE,
  STATE_FIRING,
  
}; //states for the gun. Currently very minimal, but will make expansion of functionality easier once we have a full game.

gunStates activeState = STATE_IDLE; //Setting up  avariable to store the current state.


int ammo = 10; //integer for the number of shots the player has.

unsigned long shotStartTime; //used to store the time when the player first shoots.
unsigned long shotTime = 500; //used to store how long a single shot lasts, so we can stop it after that time.
bool shotTimerStarted = false;

unsigned long delayStartTime;
unsigned long delayTime = 200;
bool delayStarted = false;

bool shotFired = false; //button can be held for as long as you want, so we use this to check if the player has fired a shot already, independent of button input. 



void setup() {
  Serial.begin(9600); //mainly for debugging, lets us see values in the IDE.

  pinMode(8, INPUT); //setting up the 8th GPIO pin as an input. We use this to track the button's state.
  pinMode(7, OUTPUT); //setting up the 7th GPIO pin as an output. We feed this into the signal pin of the laser to control it.
}



//NOTE: NEED TO CHANGE HOW AMMO IS REDUCED. WHEN ON 1 AMMO, AMMO IS REDUCED IMMEDIATELY ON SHOT START, CAUSING THE LAST SHOT TO BE IMMEDIATELY CUT OFF.



void loop() {
  Serial.println(ammo);

  if(digitalRead(8) == 1){
    activeState = STATE_FIRING;
  } //checking if the button has been pressed, and changing to the firing state.
  
  else{
    activeState = STATE_IDLE;
  } //If the button is not pressed, changing to the idle state.


  switch (activeState){

    case STATE_IDLE:
      shotFired = false; //resetting the the shotFired boolean if we enter the idle state, so the next shot functions properly.
      delayStarted = false;
      digitalWrite(7, LOW); //pushing LOW to the signal laser pin, turning it off.
      break;
    
    case STATE_FIRING:

      if(!delayStarted){
        delayStartTime = millis();
        delayStarted = true;
      }

      if(millis() > (delayStartTime + delayTime)){
        if(ammo > 0){ //checking if the player has ammo left.

          if(!shotFired) //if the player just pressed the button, shot fired should be false...
          {
            shotStartTime = millis(); //we register the start time of the shot as the current time as this code line runs.
            ammo -= 1; //taking away one shot from the ammo.
            shotFired = true; //setting shot fired to true. This way, the above line only run once per button press/ firing state.
          }

          else{

            if (millis() < (shotStartTime + shotTime)){ //checking if the current time (millis) has surpassed the start time plus the time the shot should take, if not...
              digitalWrite(7, HIGH); //send HIGH to the laser signal pin, engaging the laser.
            }

            else{ //if the shot time is surpassed...
              digitalWrite(7, LOW); //send LOW to the laser signal pin, disengaging the laser.
            }

          }
        }
      }
      break;
    
  }
}
