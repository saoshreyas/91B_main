#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int rightX, int rightY);
void resetDriveEncoders();
double avgDriveEncoderValue();

//DRIVER CONTROL FUNCTIONS
void setDriverMotors();

//AUTONOMOUS FUNCTIONS
//controls voltage, doesn't limit velocity
//using voltage allows for faster movement
void verticalMove(int units, int voltage);
void horizontalMove();

//tol = how precise, how close it can be to be fine because it will never be exact
//more precise means takes longer
void turnHeading(double target, double tol, double waitTime);