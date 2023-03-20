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
motor Motor2 = motor(PORT2, ratio18_1, false);

motor Motor10 = motor(PORT10, ratio18_1, false);

motor Motor11 = motor(PORT11, ratio18_1, false);

motor Motor20 = motor(PORT20, ratio18_1, false);

controller Controller1 = controller(primary);
motor Roller = motor(PORT19, ratio18_1, false);

motor Expand = motor(PORT3, ratio18_1, false);




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
#define ABS(N)((N < 0) ? (-N) : (N))

const int MOVING_MULTIPLIER = 10;
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

  Motor2.setVelocity(a, rpm);
  Motor11.setVelocity(a, rpm);
  Motor10.setVelocity(a2, rpm);
  Motor20.setVelocity(a2, rpm);
  Motor2.spin(pos > 0 ? forward : reverse);
  Motor11.spin(pos > 0 ? forward : reverse);
  Motor10.spin(pos2 > 0 ? reverse : forward);
  Motor20.spin(pos2 > 0 ? reverse : forward);
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
    Motor2.setStopping(brake);
    Motor10.setStopping(brake);
    Motor11.setStopping(brake);
    Motor20.setStopping(brake);
  }

  Controller1.Axis2.changed(assessMovement);
  Controller1.Axis3.changed(assessMovement);
}

void onStart() {
  printBrain("Hewwo UwU :3", true);
  Controller1.rumble(rumblePulse);
}

void rollerBackward() {
  Roller.spin(forward);
}

void rollerForward() {
  Roller.spin(reverse);
}

void rollerStop() {
  Roller.stop();
}

void initRoller() {
  Roller.setVelocity(100, percent);
  Controller1.ButtonR2.pressed(rollerForward);
  Controller1.ButtonR1.pressed(rollerBackward);
  Controller1.ButtonR1.released(rollerStop);
  Controller1.ButtonR2.released(rollerStop);
}

void expand() {
  Expand.spin(reverse);
  wait(2, seconds);
  Expand.stop();
  printBrain("Expantion", false);
}

void expandCheck() {
  printBrain("Checked", true);
  int downPressed = Controller1.ButtonRight.pressing();
  int upPressed = Controller1.ButtonLeft.pressing();
  if (downPressed && upPressed) {
    expand();
  }
}

void initExpansion() {
  printBrain("Started", false);
  Controller1.ButtonRight.pressed(expandCheck);
  Controller1.ButtonLeft.pressed(expandCheck);
}

int main() {
  onStart();
  initStearing();
  initRoller();  
  initExpansion();
}
