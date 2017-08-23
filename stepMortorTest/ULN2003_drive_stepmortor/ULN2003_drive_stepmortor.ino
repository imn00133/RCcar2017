#include <Stepper.h>

const int stepsPerRevolution=2048;
Stepper myStepper(stepsPerRevolution, 11,9,10,8);

void setup() {
  myStepper.setSpeed(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  myStepper.step(stepsPerRevolution);
  delay(500);

  myStepper.step(-stepsPerRevolution);
  delay(500);

}
