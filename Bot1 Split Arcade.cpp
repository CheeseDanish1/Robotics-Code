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
motor FrontRightDrive = motor(PORT20, ratio18_1, false);

motor BackRightDrive = motor(PORT19, ratio18_1, false);

motor FrontLeftDrive = motor(PORT10, ratio18_1, false);

motor BackLeftDrive = motor(PORT9, ratio18_1, false);

controller Controller1 = controller(primary);
motor WingRight = motor(PORT6, ratio18_1, false);

motor WingLeft = motor(PORT16, ratio18_1, false);

motor Catapult = motor(PORT8, ratio18_1, false);

encoder CatapultEncoder = encoder(Brain.ThreeWirePort.A);
motor Intake = motor(PORT18, ratio18_1, false);

motor Climb1 = motor(PORT3, ratio36_1, false);

motor Climb2 = motor(PORT13, ratio18_1, false);




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
  BackRightDrive.spin(pos > 0 ? reverse : forward);
  FrontRightDrive.spin(pos > 0 ? reverse : forward);
  BackLeftDrive.spin(pos2 > 0 ? forward : reverse);
  FrontLeftDrive.spin(pos2 > 0 ? forward : reverse);
}


void assessMovement() {
  // This is for turning (-100, 100)
  // Corresponds to x axis
  // int pos1 = Controller1.Axis3.position();
  // This is for speed(-100, 100)
  // Corresponds to y axis
  // int pos2 = Controller1.Axis2.position();

    int pos1 = -1 * Controller1.Axis1.position();
  int pos2 = Controller1.Axis3.position();


  // Dont know why this works but im glad I found it
  MoveMotors(pos2 - pos1, pos1+pos2);
  // MoveMotors(pos1, pos2);
}

void initStearing() {
  printBrain("Stearing ready", false);

  if (BRAKE_ENABLED) {
    BackRightDrive.setStopping(brake);
    BackLeftDrive.setStopping(brake);
    FrontRightDrive.setStopping(brake);
    FrontLeftDrive.setStopping(brake);
  }

  Controller1.Axis1.changed(assessMovement);
  Controller1.Axis3.changed(assessMovement);
}

void onStart() {
  printBrain("Hewwo UwU :3", true);
  Controller1.rumble(rumblePulse);
}

bool WingsOpen = false;

void openWings() {
  WingRight.spin(reverse);
  WingLeft.spin(forward);

  wait(.6, seconds);

  WingRight.stop();
  WingLeft.stop();
}

void closeWings() {
  WingRight.spin(forward);
  WingLeft.spin(reverse);

  wait(.5, seconds);

  WingRight.stop();
  WingLeft.stop();
}

void toggleWings() {
  if (WingsOpen == true) closeWings();
  if (WingsOpen == false) openWings();

  WingsOpen = !WingsOpen;
}

void initWings() {
  WingRight.setStopping(brake);
  WingLeft.setStopping(brake);

  WingRight.setVelocity(200, rpm);
  WingLeft.setVelocity(200, rpm);

  Controller1.ButtonL1.pressed(toggleWings);
  Controller1.ButtonL2.pressed(toggleWings);
}

void stopCatapult() {
  Catapult.stop();
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

void stopSpinning() {
  Intake.stop();
}

void spinIn() {
  Intake.spin(forward);
}

void spinOut() {
  Intake.spin(reverse);
}

void initIntake() {
  Intake.setVelocity(200, rpm);

  Controller1.ButtonR2.pressed(spinIn);
  Controller1.ButtonR1.pressed(spinOut);
  Controller1.ButtonR2.released(stopSpinning);
  Controller1.ButtonR1.released(stopSpinning);
}

void lowerClimb() {
  Climb1.spin(forward);
  Climb2.spin(reverse);
}

void raiseClimb() {
  Climb1.spin(reverse);
  Climb2.spin(forward);
}

void stopClimb() {
  Climb1.stop();
  Climb2.stop();
}

void initClimb() {
  Climb1.setVelocity(100, rpm);
  Climb2.setVelocity(100, rpm);
  Climb1.setMaxTorque(100, percent);
  Climb2.setMaxTorque(100, percent);

  // Climb1.setStopping(brake);
  // Climb2.setStopping(brake);

  // Controller1.ButtonUp.pressed(raiseClimb);
  Controller1.ButtonA.pressed(lowerClimb);
  Controller1.ButtonA.released(stopClimb);
  // Controller1.ButtonUp.released(stopClimb);
}

int main() {
  onStart();
  initClimb();
  initStearing();
  initWings();
  initCatapult();
  initIntake();
}
