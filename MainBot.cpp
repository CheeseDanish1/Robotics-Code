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
motor Motor1 = motor(PORT3, ratio18_1, false);

motor Motor11 = motor(PORT11, ratio18_1, false);

motor Motor2 = motor(PORT4, ratio18_1, false);

motor Motor12 = motor(PORT12, ratio18_1, false);

controller Controller1 = controller(primary);
motor Pickup = motor(PORT18, ratio18_1, false);

motor Pusher = motor(PORT19, ratio18_1, false);

motor Flywheel_1 = motor(PORT5, ratio6_1, false);

motor Expand = motor(PORT8, ratio18_1, false);

motor Roller = motor(PORT9, ratio18_1, false);




// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
#pragma endregion VEXcode Generated Robot Configuration

#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;
#define ABS(N)((N < 0) ? (-N) : (N))

const int MOVING_MULTIPLIER = 8;
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

  Motor1.setVelocity(a2, rpm);
  Motor2.setVelocity(a2, rpm);
  Motor11.setVelocity(a, rpm);
  Motor12.setVelocity(a, rpm);
  Motor1.spin(pos > 0 ? reverse : forward);
  Motor2.spin(pos > 0 ? reverse : forward);
  Motor11.spin(pos2 > 0 ? forward : reverse);
  Motor12.spin(pos2 > 0 ? forward : reverse);
}

void assessMovement() {
  // This is for turning (-100, 100)
  // Corresponds to x axis
  int pos1 = Controller1.Axis4.position();
  // This is for speed(-100, 100)
  // Corresponds to y axis
  int pos2 = Controller1.Axis3.position();

  printBrain(pos1,  true);
  printBrain(pos2, false);

  // Dont know why this works but im glad I found it
  MoveMotors(pos2 - pos1, pos2 + pos1);
}

void initStearing() {
  printBrain("Stearing ready", false);

  if (BRAKE_ENABLED) {
    Motor1.setStopping(brake);
    Motor2.setStopping(brake);
    Motor11.setStopping(brake);
    Motor12.setStopping(brake);
  }

  Controller1.Axis3.changed(assessMovement);
  Controller1.Axis4.changed(assessMovement);
}

void onStart() {
  printBrain("Hewwo UwU :3", true);
  Controller1.rumble(rumblePulse);
}

void spinPickupForwards() {
  Pickup.setVelocity(200, rpm);
  Pickup.spin(forward);
}
void spinPickupBackwards() {
  Pickup.setVelocity(200, rpm);
  Pickup.spin(reverse);
}
void stopPickup() {
  Pickup.stop();
}

void initPickup() {
  Controller1.ButtonR1.pressed(spinPickupBackwards);
  Controller1.ButtonR1.released(stopPickup);
  Controller1.ButtonR2.pressed(spinPickupForwards);
  Controller1.ButtonR2.released(stopPickup);
}

void spinPusherForwards() {
  Pusher.setVelocity(200, rpm);
  Pusher.spin(forward);
}

void spinPusherBackwards() {
  Pusher.setVelocity(200, rpm);
  Pusher.spin(reverse);
}
void stopPusher() {
  Pusher.stop();
}

void initPusher() {
  Controller1.ButtonL1.pressed(spinPusherBackwards);
  Controller1.ButtonL1.released(stopPusher);
  Controller1.ButtonL2.pressed(spinPusherForwards);
  Controller1.ButtonL2.released(stopPusher);
}

bool isSpinning = false;

void flywheel() {
  if (isSpinning == true) {
    Controller1.Screen.clearScreen();
    Flywheel_1.stop();
    isSpinning = false;
  } else {
    Flywheel_1.spin(forward);
    Controller1.Screen.clearScreen();
    Controller1.Screen.print(Flywheel_1.velocity(rpm));
    isSpinning = true;
  }
}

void initFlywheel() {
  Flywheel_1.setVelocity(600, rpm);
  Controller1.ButtonA.pressed(flywheel);
}

void rollerGoGoGo() {
  MoveMotors(5, 5);
  Roller.spin(reverse);
}

void rollerBackBackBack() {
  MoveMotors(5, 5);
  Roller.spin(forward);
}

void rollerStop() {
  Roller.stop();
  MoveMotors(0, 0);
}

void initRoller() {
  Roller.setVelocity(200, rpm);
  Controller1.ButtonX.pressed(rollerGoGoGo);  
  Controller1.ButtonB.pressed(rollerBackBackBack);  
  Controller1.ButtonX.released(rollerStop);
  Controller1.ButtonB.released(rollerStop);
}

void expand() {
  Expand.spinFor(forward, 200, degrees);
  printBrain("Expantion", false);
}

void expandCheck() {
  int downPressed = Controller1.ButtonRight.pressing();
  int upPressed = Controller1.ButtonLeft.pressing();
  if (downPressed && upPressed) {
    expand();
  }
}

void initExpansion() {
  Controller1.ButtonRight.pressed(expandCheck);
  Controller1.ButtonLeft.pressed(expandCheck);
}

int main() {
  onStart();
  initStearing();
  initPickup();
  initPusher();
  initFlywheel();
  initRoller();
  initExpansion();
}
