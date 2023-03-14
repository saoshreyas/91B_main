#include "main.h"

//task is made to prevent the entire robot from waiting for the delay

//have the same parameters for all tasks
//tasks cant have any other parameters
void indexTask(void * param)
{
  while(true)
  {
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
      indexer.set_value(false);
     //can speed this up for faster shooting
      pros::delay(50);
      indexer.set_value(true);
    }
    pros::delay(20);
  }

}