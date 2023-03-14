#include "main.h"

//implement inertial sensor here to keep auton straight
//25 min in video

//HELPER FUNCTIONS

//encoder values = measure how much a motor has spun , used to calculate the amount of units moving
void resetDriveEncoders()
{
  driverLeftBack.tare_position();
  driverLeftFront.tare_position();
  driverRightBack.tare_position();
  driverRightFront.tare_position();
}

double avgDriveEncoderValue()
{
  return (fabs(driverLeftFront.get_position()) + 
  fabs(driverLeftBack.get_position()) + 
  fabs(driverRightBack.get_position()) + 
  fabs(driverRightFront.get_position())) / 4;
}

//DRIVER CONTROLLER FUNCTIONS




//AUTONOMOUS FUNCTIONS

//Angle Normalization

//Constrains angle to -180 to 180 degrees
//allows to find the shorter degrees
//calculates the shortest angle
double normalizeAngle180(double x)
{
    x = fmod(x + 180,360);
    if (x < 0)
        x += 360;
    return x - 180;
}

//Constrains angle to 360 degrees
//make sure there are no Coterminal angles or angles more than 360
double normalizeAngle360(double x)
{
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}

void turnHeading(double target, double tol, double waitTime)
{

  auto xDriveModel = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

  bool settled = false;
  double currentAngle = normalizeAngle360(inertial.get_heading());
  //tune later
  double kP = 0.5;
  double kD = 0.5;
  double error;
  double prevError = 0;
  double finalPower = 0;
  double elapsedTime = 0;

  while (!settled)
  {
    error = normalizeAngle180(target - currentAngle);

    finalPower = (kP * error) + ((error - prevError) * kD);

    prevError = error;

    xDriveModel->rotate(finalPower);
    pros::delay(20);

    //within our tolerance
    if(abs(error) < tol)
    {
      elapsedTime += 20;
    }

    //giving a timer of how long it can wait till it has to exit
    //robot turns until it is within tolerance
    //once within tolerance it is on a timer that then exits the loop
    //waitTime is amount of time for it to adjust perfectly to the angle
    if(elapsedTime > waitTime)
    {
      settled = true;
    }
  }
  
  xDriveModel->rotate(0);
  
  
}