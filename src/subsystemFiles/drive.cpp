#include "main.h"

//implement inertial sensor here to keep auton straight
//25 min in video

//HELPER FUNCTIONS
void setDrive(int left, int rightX, int rightY){
if(abs(left) >= 0)
{
  driverLeftBack = -left;
  driverLeftFront = -left;
  driverRightBack = -left;
  driverRightFront = -left;
}
//changed from else if
if(abs(rightX) >= 0)
{
  driverLeftBack = rightX;
  driverLeftFront = -rightX;
  driverRightBack = rightX;
  driverRightFront = -rightX;
}
if(abs(rightY) >= 0)
{
  driverLeftBack = -rightY;
  driverLeftFront = -rightY;
  driverRightBack = rightY;
  driverRightFront = rightY;
}
}

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
void setDriverMotors() {
  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  int rightJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); 
  int rightJoystickY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  if(abs(leftJoystick) < 10)
    leftJoystick = 0; 
  if(abs(rightJoystickX) < 10)
    rightJoystickX = 0; 
  if(abs(rightJoystickY) < 10)
    rightJoystickY = 0; 
  setDrive(leftJoystick, rightJoystickX, rightJoystickY);
}


//AUTONOMOUS FUNCTIONS

//VOLTAGE VALUES HAVE CHANGED

void verticalMove(int units, int voltage) 
{
  //defines direction based on units provided
  //if its going backwards it will be 500 divided by -500 equating to -1
  //vice-versa
  int direction = abs(units) / units; //either will be 1 or -1
  //reset motor encoders
  resetDriveEncoders();
  //drive
  //fabs is used because get position only returns in float and abs only works for int
  while(avgDriveEncoderValue() < abs(units))
  {
    setDrive(0, 0, voltage * direction);
    //motors only update their value every 10 milliseconds
    pros::delay(10);
  }
  //brief brake
  //gets rid of momentum as the motors are on coast
  setDrive(0, 0, -10 * direction);
  //value below changes depending on weight
  pros::delay(50);
  //set drive to neutral
  setDrive(0, 0, 0);
}