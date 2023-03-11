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
void turn();