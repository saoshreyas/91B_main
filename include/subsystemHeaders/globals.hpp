#include "main.h"

//extern allows use in multiple files

//CHASIS CONTROLLER
extern std::shared_ptr<ChassisController> chassis; 


//MOTORS
extern pros::Motor flywheel;
extern pros::Motor intakeNormal;
extern pros::Motor intakeNormal2;
extern pros::Motor intakeExtra;
extern pros::Motor driverLeftBack;
extern pros::Motor driverLeftFront;
extern pros::Motor driverRightBack;
extern pros::Motor driverRightFront;


//CONTROLLER
extern pros::Controller controller;

//PISTONS
extern pros::ADIDigitalOut indexer;
extern pros::ADIDigitalOut expansion1;
extern pros::ADIDigitalOut expansion2;

//SENSORS
extern pros::Imu inertial;
