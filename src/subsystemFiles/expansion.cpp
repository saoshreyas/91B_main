#include "main.h"

void expand(){
  if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
    expansion1.set_value(true);
    expansion2.set_value(true);
}