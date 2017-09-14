#include <Stepper.h>

const int stepsPerRevolution=1024;
Stepper myStepper(stepsPerRevolution, 5,4,3,2);

void setup() {
  myStepper.setSpeed(14);
}

void loop() {
  // put your main code here, to run repeatedly:
  myStepper.step(-stepsPerRevolution);
  delay(500);

  myStepper.step(stepsPerRevolution);
  delay(500);

}
