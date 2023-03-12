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

	// inertial.reset();
	// //allowing the inertial sensor to calibrate - takes 2 seconds but extended
	// pros::delay(2500);
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
void skills()
{

}

void autonomous() 
{
	//auto xDriveModel = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());
	chassis->moveDistance(6_in);
	chassis->turnAngle(90_deg);
	
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

	while (true)
	{
		//control the drive
		// setDriverMotors();
		xDriveModel->xArcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / -1, 0.05);
		//xDriveModel->xArcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127, controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127, controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / -127, 0);
    //control the intake
		setIntakeMotors();
		//control the flywheel
		setFlywheelMotor();
		//control indexer
		index();
		//control expansion 
		expand();
		pros::delay(10);

	}
	
	
}
 