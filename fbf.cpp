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
motor Motor10 = motor(PORT10, ratio6_1, false);

motor Motor19 = motor(PORT19, ratio6_1, false);

motor Motor20 = motor(PORT20, ratio6_1, false);

motor Motor9 = motor(PORT9, ratio18_1, false);

motor Motor8 = motor(PORT8, ratio6_1, false);

motor Motor4 = motor(PORT4, ratio18_1, false);

motor Motor5 = motor(PORT5, ratio18_1, false);


// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;




#pragma endregion VEXcode Generated Robot Configuration

#include "vex.h"
#define ABS(N) ((N<0)?(-N):(N))
// Allows for easier use of the VEX Library
using namespace vex;

const int MOVING_MULTIPLIER = 6;
const int clampVelocity = 75;
bool band = false;
// Motor 1 and 9 are the right motors and are ports 10 and 9
// Motor 2 and 10 are the left motors and are port 19 and 20
// Motor 3 is the spinny band and goes to port 11

template<class Any>
Any printBrain(Any val) { 
  Brain.Screen.clearLine(1);
  Brain.Screen.clearScreen();
  Brain.Screen.print(val); 
  return val; 
}

void MoveMotors(int pos, int pos2) {
  int a = ABS(pos)*MOVING_MULTIPLIER;
  int a2 = ABS(pos2)*MOVING_MULTIPLIER;

  Motor20.setVelocity(a, rpm);
  Motor20.spin(pos < 0 ? forward : reverse);
  Motor19.setVelocity(a, rpm);
  Motor19.spin(pos < 0 ? forward : reverse);
  Motor10.setVelocity(a2, rpm);
  Motor10.spin(pos2 < 0 ? reverse : forward);
  Motor9.setVelocity(a2, rpm);
  Motor9.spin(pos2 < 0 ? reverse : forward);
}

void assessMovement() {
  // This is for turning (-100, 100)
  // Corresponds to x axis
  int pos1 = Controller1.Axis4.position();
  // This is for speed(-100, 100)
  // Corresponds to y axis
  int pos2 = Controller1.Axis3.position();
  
  // Dont know why this works but im glad I found it
  MoveMotors(pos2-pos1, pos2+pos1);
}

void clampDown() {
  Motor4.setVelocity(clampVelocity, rpm);
  Motor5.setVelocity(clampVelocity, rpm);
  Motor4.spin(reverse);
  Motor5.spin(forward);
}

void clampUp() {
  Motor4.setVelocity(clampVelocity, rpm);
  Motor5.setVelocity(clampVelocity, rpm);
  Motor4.spin(forward );
  Motor5.spin(reverse);
}

void clampStop() {
Motor4.stop();
Motor5.stop();
}

void startBand() {
  Motor8.setVelocity(400, rpm);
  Motor8.spin(forward);
}

void reverseBand() {
  Motor8.setVelocity(400, rpm);
  Motor8.spin(reverse);
}

void stopBand() {
  Motor8.stop();
}

void initBand() {
  Controller1.ButtonR1.pressed(startBand);
  Controller1.ButtonR1.released(stopBand);
  Controller1.ButtonR2.pressed(reverseBand);
  Controller1.ButtonR2.released(stopBand);
}

// void startBand() {
//   Motor8.setVelocity(400, rpm);
//   band = !band;
//   if (band) {
//     Motor8.spin(reverse);
//   } else {
//     Motor8.stop();
//   }
// }

// void reverseBand() {
//   Motor8.setVelocity(400, rpm);
//   Motor8.spin(reverse);
// }

// void stopBand() {
//   Motor8.stop();
// }

// void initBand() {
//   Controller1.ButtonR1.pressed(startBand);
//   Controller1.ButtonR2.pressed(startBand);
//   // Controller1.ButtonR2.pressed(reverseBand);
// }

void initClamp() {
  Controller1.ButtonL2.pressed(clampDown);
  Controller1.ButtonL2.released(clampStop);
  Controller1.ButtonL1.pressed(clampUp);
  Controller1.ButtonL1.released(clampStop);

}

void initStearing() {
  Controller1.Axis3.changed(assessMovement);
  Controller1.Axis4.changed(assessMovement);
}

void onStart() {
  printBrain("Hewwo UwU :3");
  Controller1.rumble(rumblePulse);
}

int main() {
  Motor4.setStopping(brake);
  Motor5.setStopping(brake);
  onStart();
  initBand();
  initStearing();
  initClamp();
}
