#include "main.h"

int mode = 0;
int mode1 = 0;

//HELPER FUNCTIONS
void setFlywheel(int power)
{
  flywheel = power;
}

//DRIVER CONTROL FUNCTIONS
void setFlywheelMotor() 
{

  if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
  {
    setFlywheel(-75.25); 
  }
  if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
  {
    setFlywheel(0); 
  }
  if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
  {
    setFlywheel(50); 
  }
  // //normal shooting
  // if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
  // {
  //   mode++;
  // }

  // if(mode > 1)
  // {
  //   mode = 0;
  // }

  // if(mode == 0)
  // {
  //   setFlywheel(0);
  // }

  // if(mode == 1)
  // {
  //   //adjust the speed value
  //   setFlywheel(-75.25);
  // }

}

