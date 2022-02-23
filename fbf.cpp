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
controller Controller1 = controller(primary);
motor Motor1 = motor(PORT1, ratio6_1, false);

motor Motor2 = motor(PORT11, ratio6_1, false);

motor Motor10 = motor(PORT10, ratio6_1, false);

motor Motor9 = motor(PORT9, ratio18_1, false);


// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;




#pragma endregion VEXcode Generated Robot Configuration

#include "vex.h"
#define ABS(N) ((N<0)?(-N):(N))
// Allows for easier use of the VEX Library
using namespace vex;

const int MOVING_MULTIPLIER = 6;

// Motor 1 is the right motor
// Motor 2 is the left motor

void start() {
  Brain.Screen.clearLine(1);
  Brain.Screen.clearScreen();
  Brain.Screen.print("Hewwo UwU <3");
}

void MoveRightMotor() {
  int pos = Controller1.Axis2.position();
  int a = ABS(pos)*MOVING_MULTIPLIER;
  Motor2.setVelocity(a, rpm);
  Motor2.spin(pos > 0 ? reverse : forward);
  Motor10.setVelocity(a, rpm);
  Motor10.spin(pos > 0 ? reverse : forward);
}

void MoveLeftMotor() {
  int pos = Controller1.Axis3.position();
  int a = ABS(pos)*MOVING_MULTIPLIER;
  Motor1.setVelocity(a, rpm);
  Motor1.spin(pos > 0 ? forward : reverse);
  Motor9.setVelocity(a, rpm);
  Motor9.spin(pos > 0 ? forward : reverse);
}

int whenStarted1() {
  start();
  Controller1.Axis3.changed(MoveLeftMotor);
  Controller1.Axis2.changed(MoveRightMotor);
  return 0;
}

int main() {
  whenStarted1();
}
