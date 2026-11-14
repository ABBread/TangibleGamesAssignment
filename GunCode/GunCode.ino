
enum gunStates{
  STATE_IDLE,
  STATE_READY,
  STATE_FIRING,
  
}; //states for the gun. Currently quite minimal, but will make expansion of functionality easier once we have a full game.

gunStates activeState = STATE_IDLE; //Setting up  avariable to store the current state.


int ammo = 10; //integer for the number of shots the player has.

unsigned long shotStartTime; //used to store the time when the player first shoots.
unsigned long shotTime = 500; //used to store how long a single shot lasts, so we can stop it after that time.

unsigned long delayStartTime; //used to store when the player first presses the button to shoot.
unsigned long delayTime = 200; //used to store the delay time before registering a full button press.
bool delayStarted = false; //boolean to make sure we only delay for one full cycle each press.

bool shotFired = false; //button can be held for as long as you want, so we use this to check if the player has fired a shot already, independent of button input. 



void setup() {
  Serial.begin(9600); //mainly for debugging, lets us see values in the IDE.

  pinMode(8, INPUT); //setting up the 8th GPIO pin as an input. We use this to track the button's state.
  pinMode(7, OUTPUT); //setting up the 7th GPIO pin as an output. We feed this into the signal pin of the laser to control it.
}



void loop() {
  if(activeState != STATE_FIRING){ 
    /*we don't want the nested logic to run when in the firing state, as any interruptions to that state
     cause the laser shot itself to get cut off. we simply wait for the state to exit naturally.*/ 

    if(digitalRead(8) == 1){
      activeState = STATE_READY;
    } //checking if the button has been pressed, and changing to the ready state.
    
    else{ 
      activeState = STATE_IDLE;
    } //If the button is not pressed, changing to the idle state.
  }

  switch (activeState){ //switch is clean for handling behaviour in each state.

    case STATE_IDLE:
      shotFired = false; //resetting the the shotFired boolean if we enter the idle state, so the next shot functions properly.
      delayStarted = false; //same for the delay boolean as above.
      digitalWrite(7, LOW); //pushing LOW to the signal laser pin, turning it off.
      break;
    

    case STATE_READY:
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
            activeState = STATE_FIRING; // Since we've completed all checks and logic to prepare a shot, we enter the firing state.
          }
        }
      }
      break;
    

    case STATE_FIRING:
      if (millis() > (shotStartTime + shotTime)){ //checking if the current time (millis) has surpassed the start time plus the time the shot should take
        digitalWrite(7, LOW); //turning off the laser as the shot time is over.
        if(digitalRead(8) == 0){ //checking for the player letting go of the button.
          activeState = STATE_IDLE; //going back to the idle state.
        }
      }
      else{
        digitalWrite(7, HIGH); //making the laser enagage as we are in the firing state and the shot time has not yet elapsed.
      }
      break;
  }
}
