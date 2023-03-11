#include "main.h"

//CHASIS CONTROLLER
std::shared_ptr<ChassisController> chassis = 

ChassisControllerBuilder()

  //Defines the Motors for the Chassis 

  .withMotors( 

  -16,//Left Front Wheel; using a negative value reverse direction of motor 

  10, //Right Front Wheel; using a negative value reverse direction of motor 

  20, //Right Back Wheel; using a negative value reverse direction of motor 

  -18 //Left Back Wheel; using a negative value reverse direction of motor 

  ) 

  // Defines the Dimensions for the Chassis 

  //FIND OUT TRACK TOMMOROW

  //Green gearset, external ratio of (36.0 / 60.0), 3.25 inch wheel diameter, 11.5 inch wheel track 

  .withDimensions({AbstractMotor::gearset::green, (60.0 / 36.0)}, {{3.25_in, 11.5_in}, imev5GreenTPR})	 

  //Defines Gains for the chassis 

  .withGains( 

    //kP, kI, kD
    {0.002, 0, 0.0001}, // Distance controller gains 

    {0, 0, 0}, // Turn controller gains 

    {0, 0, 0}  // Angle controller gains (helps drive straight) 

  ) 

  //Defines max velocity of chassis based on gearset 
  //WHY CHANGE THE DEFAULT?

  .withMaxVelocity(200) 

  //Logs what the controller does into the terminal
  .withLogger
  (
    std::make_shared<Logger>
    (
        TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::debug // Most verbose log level
    )
  )

  //Build Your Chassis Model! 

  .build(); 

  


//MOTORS
// port?, motor rpm, direction false - normal and true - reverse, how the motor moves

//Keeping Flywheel at Blue motor setting
pros::Motor flywheel(7, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeNormal(17, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeExtra(19, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
//NextFlywheel
pros::Motor driverLeftBack(18, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
//AcrossFlywheel
pros::Motor driverLeftFront(16, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
//UnderFlywheel
pros::Motor driverRightBack(20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
//Behind Flywheel
pros::Motor driverRightFront(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//PISTONS
pros::ADIDigitalOut indexer('B', true);
pros::ADIDigitalOut expansion1('A', false);
pros::ADIDigitalOut expansion2('G', false);

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//SENSORS
pros::Imu inertial(21);


