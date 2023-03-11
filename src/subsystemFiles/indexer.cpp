#include "main.h"

void index()
{
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
  {
    indexer.set_value(false);
    //can speed this up for faster shooting
    pros::delay(50);
    indexer.set_value(true);
  }
}