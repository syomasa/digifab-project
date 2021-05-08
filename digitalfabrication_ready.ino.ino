#include <Stepper.h>

#define ECHO_PIN 2
#define TRIG_PIN 3

// state machines
enum rotation{LEFT=0,RIGHT=1};
enum runstate{WAIT=0, RUN=1};

enum rotation rot_direction = LEFT;
enum runstate run_state = WAIT;

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setState(int threshold) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int distance = pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;

  if(distance <= threshold) {
    run_state = RUN;
    rot_direction = (enum rotation)((int)rot_direction + 1) % 2;
  }
}
void setRotation(Stepper stepper) {
  if(run_state == RUN && rot_direction == RIGHT) {
    stepper.step(stepsPerRevolution * 4/5);
  } else if(run_state == RUN && rot_direction == LEFT) {
      stepper.step(-stepsPerRevolution * 4/5);
  }
  run_state = WAIT;
}

void setup() {
  // PINS
  pinMode(ECHO_PIN,INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  
  // set the speed at 60 rpm:
  myStepper.setSpeed(5);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  setState(8);
  setRotation(myStepper);  
}
