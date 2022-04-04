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

void clampDown() {
  Motor4.spin(reverse);
  Motor5.spin(forward);
}

void clampUp() {
  Motor4.spin(forward );
  Motor5.spin(reverse);
}

void clampStop() {
Motor4.stop();
Motor5.stop();
}

void startBand() {
  Motor8.spin(forward);
}

void reverseBand() {
  Motor8.spin(reverse);
}

void stopBand() {
  Motor8.stop();
}

void initBand() {
  Motor8.setVelocity(400, rpm);
  Controller1.ButtonR1.pressed(startBand);
  Controller1.ButtonR1.released(stopBand);
  Controller1.ButtonR2.pressed(reverseBand);
  Controller1.ButtonR2.released(stopBand);
}

void initClamp() {
  Motor4.setVelocity(clampVelocity, rpm);
  Motor5.setVelocity(clampVelocity, rpm);
  Controller1.ButtonL2.pressed(clampDown);
  Controller1.ButtonL2.released(clampStop);
  Controller1.ButtonL1.pressed(clampUp);
  Controller1.ButtonL1.released(clampStop);
}

void moveForwards(int inchess) {
  int speed = 600
  Motor20.setVelocity(speed, rpm);
  Motor19.setVelocity(speed, rpm);
  Motor10.setVelocity(speed, rpm);
  Motor9.setVelocity(speed, rpm);

  int rps = speed/60;
  // 1 second there is 10 rotations and each rotation covers 4 pi inches 
  // 1 second there is 10 * 4 pi inches covered
  // 1 second / 10*4pi = x/inchess
  float rotateFor = inchess/(rps*4*3.1415926535897932384626433)

  Motor20.spin(forward);
  Motor19.spin(forward);
  Motor10.spin(forward);
  Motor9.spin(forward);

  wait(rotateFor, seconds);

  Motor20.stop();
  Motor19.stop();
  Motor10.stop();
  Motor9.stop();
}
void initStearing() {
 moveForwards(12); 
}

void onStart() {
  printBrain("Hewwo UwU :3");
  Controller1.rumble(rumblePulse);
}

int main() {
  Motor4.setStopping(brake);
  Motor5.setStopping(brake);
  // onStart();
  // initBand();
  initStearing();
  // initClamp();
}
