#include "main.h"

//HELPER FUNCTIONS
void setFlywheel(int power){
  flywheel = power;
}

//DRIVER CONTROL FUNCTIONS
void setFlywheelMotor() {
  int flywheelPower = -127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
  setFlywheel(flywheelPower);
}