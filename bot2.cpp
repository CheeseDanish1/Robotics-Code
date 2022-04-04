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
motor Motor3 = motor(PORT3, ratio18_1, false);

motor Motor4 = motor(PORT7, ratio6_1, false);

motor Motor9 = motor(PORT20, ratio18_1, false);

motor Motor10 = motor(PORT1, ratio18_1, false);

motor Motor20 = motor(PORT10, ratio18_1, false);

motor Motor19 = motor(PORT2, ratio18_1, false);

controller Controller1 = controller(primary);
motor Motor8 = motor(PORT8, ratio18_1, false);


// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;




#pragma endregion VEXcode Generated Robot Configuration

#include "vex.h"
#define ABS(N) ((N<0)?(-N):(N))
// Allows for easier use of the VEX Library
using namespace vex;

const int MOVING_MULTIPLIER = 6;
const int clampVelocity = 200;
// bool band = false;
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

  if (pos == 0 && pos2 == 0) {
    Motor20.stop();
    Motor19.stop();
    Motor10.stop();
    Motor9.stop();
  }

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
  Motor4.spin(reverse);
}

void clampUp() {
  Motor4.setVelocity(clampVelocity, rpm);
  Motor4.spin(forward );
}

void clampStop() {
Motor4.stop();
}

void startBand() {
  Motor8.setVelocity(500, rpm);
  Motor8.spin(forward);
}

void reverseBand() {
  Motor8.setVelocity(500, rpm);
  Motor8.spin(reverse);
}

void stopBand() {
  Motor8.stop();
}

void guiderStop() {
  Motor3.stop();
}
void guiderUp() {
  Motor3.setVelocity(75, rpm);
  Motor3.spin(forward);
}

void guiderDown() {
  Motor3.setVelocity(75, rpm);
  Motor3.spin(reverse);
}

void initBand() {
  Controller1.ButtonR1.pressed(startBand);
  Controller1.ButtonR1.released(stopBand);
  Controller1.ButtonR2.pressed(reverseBand);
  Controller1.ButtonR2.released(stopBand);
}

void initClamp() {
  Controller1.ButtonB.pressed(clampDown);
  Controller1.ButtonB.released(clampStop);
  Controller1.ButtonX.pressed(clampUp);
  Controller1.ButtonX.released(clampStop);

}

void initStearing() {
  Motor20.setStopping(brake);
  Motor19.setStopping(brake);
  Motor10.setStopping(brake);
  Motor9.setStopping(brake);
  Controller1.Axis3.changed(assessMovement);
  Controller1.Axis4.changed(assessMovement);
}

void initGuider() {
  Controller1.ButtonL1.pressed(guiderDown);
  Controller1.ButtonL1.released(guiderStop);
  Controller1.ButtonL2.pressed(guiderUp);
  Controller1.ButtonL2.released(guiderStop);
}

void onStart() {
  printBrain("Hewwo UwU :3");
  Controller1.rumble(rumblePulse);
}

int main() {
  Motor4.setStopping(hold);
  Motor3.setStopping(hold);
  onStart();
  initBand();
  initStearing();
  initClamp();
  initGuider();
}
