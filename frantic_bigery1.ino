// Definitions
enum motorStates{RIGHT, LEFT};
enum motorStates turn = RIGHT;

enum states{WAIT=0,RUN=1};
enum states runState = WAIT;

// PIR-sensor
const int PIRPIN = 13;

// Test button
//const int buttonPin = 8;

// State updater
void setState() {
  if(digitalRead(PIRPIN) == 1) {
    runState = RUN;
    turn = (enum motorStates)(((int)turn + 1) % 2);
    delay(500);
  }
}

//Motor

const int motorPin1  = 10; // Pin  7 of L293
const int motorPin2  = 9;  // Pin  2 of L293


void chooseRotation() {
  if(runState == WAIT) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  } else if(runState == RUN && turn == RIGHT) {
    	digitalWrite(motorPin1, HIGH);
    	digitalWrite(motorPin2, LOW);
    	delay(2000);
    	runState = WAIT;

  } else if(runState == RUN && turn == LEFT) {
    	digitalWrite(motorPin1, LOW);
    	digitalWrite(motorPin2, HIGH);
    	delay(2000);
    	runState = WAIT;
  }
}

//This will run only one time.
void setup(){
 
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
  	//pinMode(buttonPin, INPUT_PULLUP);
  	pinMode(PIRPIN, INPUT);
  
  	// Set stepper speed
  	Serial.begin(9600);
}


void loop(){
  setState();
  chooseRotation();
  Serial.println(digitalRead(PIRPIN));
}
