#include "main.h"

//fields


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	//line number starts at 0, 
	pros::lcd::set_text(1, "91B's Robot");

	//sets motors like this from the very start
	driverLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driverLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driverRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driverRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	//keeping on hold but can change to coast if needed
	intakeNormal.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intakeExtra.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	indexer.set_value(true);
	expansion1.set_value(false);
	expansion2.set_value(false);

	pros::Task indexerTask(indexTask);


	inertial.reset();
  while(inertial.is_calibrating())
	{
		pros::delay(20);
	}

  //// string controls how many times it jolts
	//// good for debugging
	controller.rumble("---");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void timeMove(int distance)
{
	auto xDriveModel = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

	int elapsedTime = 0;
	while(true)
	{
		xDriveModel->forward(distance);
		pros::delay(20);
		elapsedTime += 20;
		if(elapsedTime > 1000)
		{
			break;
		}
	}
	xDriveModel->stop();
}

void testing()
{
	//chassis->moveDistance(-14.5_in);

	//turn 90 degrees and get between 89-91 degrees and is given 250 ms to settle seconds
	//usual one
	std::cout<< std::to_string(inertial.get_heading()) + "\n";
	turnHeading(90, 1, 250);
	std::cout<< "hi \n";

	chassis->moveDistance(3_in);
	pros::delay(20);

	std::cout<< std::to_string(inertial.get_heading()) + "\n";
	turnHeading(0, 1, 250);
	std::cout<< "hi \n";
	pros::delay(20);
	std::cout<< std::to_string(inertial.get_heading()) + "\n";
	turnHeading(90, 1, 250);
	std::cout<< "hi \n";
	std::cout<< std::to_string(inertial.get_heading()) + "\n";
	
	// int elapsedTime = 0;
	// while(true)
	// {
	// 	xDriveModel->forward(50);
	// 	pros::delay(20);
	// 	elapsedTime += 20;
	// 	if(elapsedTime > 1000)
	// 	{
	// 		break;
	// 	}
	// }
	// xDriveModel->stop();
}

void skills()
{
	//get roller 1
    chassis->moveDistance(1.5_in);
    setIntake(127);
    pros::delay(200);
    setIntake(0);
    //back up from roller 1
    chassis->moveDistance(-0.75_in);
    //face disk 
    turnHeading(135, 1, 250);
    //move and intake disk
    chassis->setMaxVelocity(50);
    setIntake(-127);
    chassis->moveDistance(7_in);
    setIntake(0);

    //turn to roller 2
		chassis->setMaxVelocity(127);
    turnHeading(90, 2, 250);

    //get roller 2
    chassis->setMaxVelocity(100);
		timeMove(15);
    //chassis->moveDistance(1.35_in);
    setIntake(-127);
    pros::delay(200);
    setIntake(0);

    //back up from roller 2
    chassis->moveDistance(-2.5_in);
    turnHeading(0, 1.5, 250);
		std::cout<< std::to_string(inertial.get_heading()) + "\n";
		
		pros::delay(20);

    //drive towards highgoal
		chassis->setMaxVelocity(127);
    chassis->moveDistance(-14.5_in);
    turnHeading(10.5, 1.5, 250);
		std::cout<< std::to_string(inertial.get_heading()) + "\n";


    //start Flywheel
    setFlywheel(-85.25);
    pros::delay(2250);
    //shoot
    indexer.set_value(false);
    //can speed this up for faster shooting
    pros::delay(100);
    indexer.set_value(true);
    pros::delay(300);
    indexer.set_value(false);
    //can speed this up for faster shooting
    pros::delay(100);
    indexer.set_value(true);
    pros::delay(200);
    indexer.set_value(false);
    //can speed this up for faster shooting
    pros::delay(100);
    indexer.set_value(true);
    pros::delay(200);
    setFlywheel(0);

    //revert to facing normal direction
    turnHeading(0, 2, 250);

    //move backward to be line with first disk in row
		chassis->moveDistance(7_in);
		turnHeading(270, 2, 250);
		
		//move towards disc line and intake disc one
    chassis->setMaxVelocity(50);
    setIntake(-127);
    chassis->moveDistance(7_in);
    setIntake(0);

    //turn to face the disk line
		turnHeading(225, 3, 250);
		

    //intake all three disks
		chassis->setMaxVelocity(50);
    setIntake(-127);
    chassis->moveDistance(12_in);
    setIntake(0);

    //face high goal
		turnHeading(315, 3, 250);

    //shoot 
    setFlywheel(-85.25);
    pros::delay(2250);
    //shoot
    indexer.set_value(false);
    //can speed this up for faster shooting
    pros::delay(100);
    indexer.set_value(true);
    pros::delay(300);
    indexer.set_value(false);
    //can speed this up for faster shooting
    pros::delay(100);
    indexer.set_value(true);
    pros::delay(200);
    indexer.set_value(false);
    //can speed this up for faster shooting
    pros::delay(100);
    indexer.set_value(true);
    pros::delay(200);
    setFlywheel(0);

    //face three stack
		turnHeading(225, 3, 250);

    //knock over three stack
		chassis->moveDistance(12_in);

    //intake disks in three stack
		chassis->setMaxVelocity(50);
    setIntake(-127);
    chassis->moveDistance(12_in);
    setIntake(0);

    //turn to face high goal
    //move towards high goal
    //shoot in high goal
    //back up to point where robot is in front of roller #3
    //turn to face roller #3
    //move forward and roll roller #3
    //back up 
    //face disk
    //move and intake disk
    //turn to face roller #4
    //get roller #4
    //back up and move to expanding position
    //expand
}

void autonomous() 
{

	auto xDriveModel = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

	//skills();

	testing();

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() 
{
	auto xDriveModel = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

	std::cout << (inertial.get_heading()) << std::endl;
	pros::delay(20);

	while (true)
	{
		//control the drive
		// setDriverMotors();
		xDriveModel->xArcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0, controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0, controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / -127.0, 0.05);
    //control the intake
		setIntakeMotors();
		//control the flywheel
		setFlywheelMotor();
		//control indexer

		//control expansion 
		expand();
		pros::delay(10);

	}
	
	
}
 