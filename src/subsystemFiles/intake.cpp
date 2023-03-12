#include "main.h"

//HELPER FUNCTIONS
void setIntake(int power){
  intakeNormal = power;
  intakeNormal2 = power;
  intakeExtra = power;
}

//DRIVER CONTROL FUNCTIONS
void setIntakeMotors() {
  int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_B));
  setIntake(intakePower);
}