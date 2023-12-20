#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor BackRightDrive = motor(PORT10, ratio18_1, false);

motor BackLeftDrive = motor(PORT11, ratio18_1, false);

motor FrontRightDrive = motor(PORT2, ratio18_1, false);

motor FrontLeftDrive = motor(PORT20, ratio18_1, false);

motor Catapult = motor(PORT15, ratio18_1, false);

motor WingRight = motor(PORT4, ratio18_1, false);

motor WingLeft = motor(PORT7, ratio18_1, false);

motor IntakeLeft = motor(PORT18, ratio18_1, false);

motor IntakeRight = motor(PORT12, ratio18_1, false);

controller Controller1 = controller(primary);
encoder CatapultEncoder = encoder(Brain.ThreeWirePort.A);



// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;
#define ABS(N)((N < 0) ? (-N) : (N))

const int MOVING_MULTIPLIER = 2;
bool BRAKE_ENABLED = true;

template < class Any >
  Any printBrain(Any val, bool clear2) {
    if (clear2) {
      Brain.Screen.clearLine(1);
      Brain.Screen.clearScreen();
    } else {
      Brain.Screen.newLine();
    }
    Brain.Screen.print(val);
    return val;
  }

void MoveMotors(int pos, int pos2) {
  int a = ABS(pos) * MOVING_MULTIPLIER;
  int a2 = ABS(pos2) * MOVING_MULTIPLIER;

  BackRightDrive.setVelocity(a, rpm);
  FrontRightDrive.setVelocity(a, rpm);
  BackLeftDrive.setVelocity(a2, rpm);
  FrontLeftDrive.setVelocity(a2, rpm);
  BackRightDrive.spin(pos > 0 ? forward : reverse);
  FrontRightDrive.spin(pos > 0 ? forward : reverse);
  BackLeftDrive.spin(pos2 > 0 ? reverse : forward);
  FrontLeftDrive.spin(pos2 > 0 ? reverse : forward);
}


void assessMovement() {
  // This is for turning (-100, 100)
  // Corresponds to x axis
  int pos1 = Controller1.Axis3.position();
  // This is for speed(-100, 100)
  // Corresponds to y axis
  int pos2 = Controller1.Axis2.position();

  // Dont know why this works but im glad I found it
  MoveMotors(pos1, pos2);
}

void initStearing() {
  printBrain("Stearing ready", false);

  if (BRAKE_ENABLED) {
    BackRightDrive.setStopping(brake);
    BackLeftDrive.setStopping(brake);
    FrontRightDrive.setStopping(brake);
    FrontLeftDrive.setStopping(brake);
  }

  Controller1.Axis3.changed(assessMovement);
  Controller1.Axis2.changed(assessMovement);
}

void onStart() {
  printBrain("Hewwo UwU :3", true);
  Controller1.rumble(rumblePulse);
}

void intakeForward() {
  IntakeLeft.spin(forward);
  IntakeRight.spin(reverse);
}

void intakeReverse() {
  IntakeLeft.spin(reverse);
  IntakeRight.spin(forward);
}

void intakeStop() {
  IntakeLeft.stop();
  IntakeRight.stop();
}

void initIntake() {
  IntakeLeft.setStopping(brake);
  IntakeRight.setStopping(brake);

  IntakeLeft.setVelocity(200, rpm);
  IntakeRight.setVelocity(200, rpm);

  Controller1.ButtonR1.pressed(intakeReverse);
  Controller1.ButtonR2.pressed(intakeForward);
  Controller1.ButtonR2.released(intakeStop);
  Controller1.ButtonR1.released(intakeStop);
}

bool WingsOpen = false;

void openWings() {
  WingRight.spin(reverse);
  WingLeft.spin(forward);

  wait(.29, seconds);

  WingRight.stop();
  WingLeft.stop();
}

void closeWings() {
  WingRight.spin(forward);
  WingLeft.spin(reverse);

  wait(.35, seconds);

  WingRight.stop();
  WingLeft.stop();
  // WingRight.spinFor(forward, 180, degrees);
  // WingLeft.spinFor(reverse, 180, degrees);
}

void toggleWings() {
  if (WingsOpen == true) closeWings();
  if (WingsOpen == false) openWings();

  WingsOpen = !WingsOpen;
}

void initWings() {
  WingRight.setStopping(brake);
  WingLeft.setStopping(brake);

  WingRight.setVelocity(150, rpm);
  WingLeft.setVelocity(150, rpm);

  Controller1.ButtonA.pressed(toggleWings);

  // Controller1.ButtonR2.pressed(openWings);
  // Controller1.ButtonL2.pressed(closeWings);
}

void stopCatapult() {
  Catapult.stop();
  IntakeLeft.stop();
}

void shootCatapult() {
  int encoderAngle = CatapultEncoder.position(degrees);
  int isPressed = Controller1.ButtonY.pressing();

  while (isPressed) {
    Catapult.spin(reverse);
    printBrain(encoderAngle, true);
    
    if (encoderAngle < -60) {
      Catapult.stop();
      wait(.5, seconds);
      Catapult.spin(reverse);
      wait(.3, seconds);
    }

    encoderAngle = CatapultEncoder.position(degrees);
    isPressed = Controller1.ButtonY.pressing();
  }
  Catapult.stop();
} 

void initCatapult() {
  Catapult.setStopping(brake);
  Catapult.setVelocity(200, rpm);
  
  Controller1.ButtonY.pressed(shootCatapult);
}

int main() {
  onStart();
  initStearing();
  initWings();
  initIntake();
  initCatapult();
}

/* *************WIRING*************

BACK RIGHT DRIVE: PORT 10
BACK LEFT DRIVE: PORT 11
FRONT RIGHT DRIVE: PORT 2
FRONT LEFT DRIVE: PORT 20

CATAPULT: PORT 15

RIGHT WING: PORT 4
LEFT WING: PORT 7

LEFT INTAKE: PORT 18
RIGHT INTAKE: PORT 12

*/
