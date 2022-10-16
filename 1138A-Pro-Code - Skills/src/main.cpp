/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//XCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    2, 11, 3, 20    
// Endgame              motor         5               
// Flywheel             motor         7               
// Roller               motor         8               
// Intake               motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  Drivetrain.setStopping(coast);
  Flywheel.setStopping(coast);
  Intake.setStopping(coast);
  Roller.setStopping(coast);
  Endgame.setStopping(hold);
  // Auton starts here:  

  //Roller Code:
  Drivetrain.driveFor(reverse, 3, inches);
  Roller.spinFor(forward, 0.5, rev);
  // Flywheel.spinFor(forward, 200, rev, 570, rpm, false);
  // Drivetrain.driveFor(forward, 1.5, inches);
  // Flywheel.stop();
  // Flywheel.spinFor(forward, 200, rev, 100, rpm, false);
  // Drivetrain.driveFor(reverse, 2.6, inches , 400, rpm, false);
  // Roller.spinFor(reverse, .5, rev);
  // Drivetrain.driveFor(forward,  2, inches);
  // Drivetrain.turnFor(8, degrees);
  // wait(6, seconds);
  // Intake.spinFor(reverse, 2, rev);
  // wait(3, seconds);
  // Intake.spinFor(reverse, 2.8, rev);
  
  // Drivetrain.turnFor(-27, degrees);
  // Drivetrain.driveFor(forward,  15, inches);
  // Drivetrain.turnFor(47, degrees,false);


  //Skills cont:
  // Drivetrain.turnFor(100, degrees, 300, rpm);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
   Drivetrain.setStopping(coast);
   Flywheel.setStopping(coast);
   Intake.setStopping(coast);
   Roller.setStopping(coast);
   Endgame.setStopping(hold);
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
