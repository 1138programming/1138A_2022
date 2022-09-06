#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor leftMotorA = motor(PORT2, ratio18_1, false);
motor leftMotorB = motor(PORT11, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT20, ratio18_1, true);
motor rightMotorB = motor(PORT3, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
inertial DrivetrainInertial = inertial(PORT19);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 2.625);
motor Roller = motor(PORT1, ratio18_1, false);
motor Intake = motor(PORT9, ratio18_1, false);
motor Flywheel = motor(PORT10, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

// define variables used for controlling motors based on controller inputs
bool Controller2LeftShoulderControlMotorsStopped = true;
bool Controller2RightShoulderControlMotorsStopped = true;
bool Controller2UpDownButtonsControlMotorsStopped = true;
bool Controller2XABYButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller2
int rc_auto_loop_function_Controller2() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonL1/ButtonL2 status to control Roller
      if (Controller2.ButtonL1.pressing()) {
        Roller.spin(forward);
        Controller2LeftShoulderControlMotorsStopped = false;
      } else if (Controller2.ButtonL2.pressing()) {
        Roller.spin(reverse);
        Controller2LeftShoulderControlMotorsStopped = false;
      } else if (!Controller2LeftShoulderControlMotorsStopped) {
        Roller.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller2LeftShoulderControlMotorsStopped = true;
      }
      // check the ButtonR1/ButtonR2 status to control Intake
      if (Controller2.ButtonR1.pressing()) {
        Intake.spin(forward);
        Controller2RightShoulderControlMotorsStopped = false;
      } else if (Controller2.ButtonR2.pressing()) {
        Intake.spin(reverse);
        Controller2RightShoulderControlMotorsStopped = false;
      } else if (!Controller2RightShoulderControlMotorsStopped) {
        Intake.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller2RightShoulderControlMotorsStopped = true;
      }
      // check the X/A/Y/Z buttons status to control Flywheel

      if (Controller2.ButtonX.pressing()) {
        Flywheel.spin(forward, 100, percent);
        Controller2XABYButtonsControlMotorsStopped = false;
      } else if (Controller2.ButtonA.pressing()) {
        Flywheel.spin(forward, 75, percent);
        Controller2XABYButtonsControlMotorsStopped = false;
      } else if (Controller2.ButtonB.pressing()) {
        Flywheel.spin(forward, 50, percent);
        Controller2XABYButtonsControlMotorsStopped = false;
      } else if (Controller2.ButtonY.pressing()) {
        Flywheel.spin(forward, 25, percent);
        Controller2XABYButtonsControlMotorsStopped = false;  
      } else if (!Controller2XABYButtonsControlMotorsStopped) {
        Flywheel.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller2XABYButtonsControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  wait(200, msec);
  DrivetrainInertial.calibrate();
  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  // wait for the Inertial calibration process to finish
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
  task rc_auto_loop_task_Controller2(rc_auto_loop_function_Controller2);
  wait(50, msec);
  Brain.Screen.clearScreen();
}