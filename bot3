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

motor Motor2 = motor(PORT2, ratio6_1, false);

motor Motor3 = motor(PORT3, ratio18_1, false);

motor Motor4 = motor(PORT4, ratio18_1, false);


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
#define ABS(N) ((N<0)?(-N):(N))

// Allows for easier use of the VEX Library
using namespace vex;

int MOVING_MULTIPLIER = 8;

template<class Any>
Any printSpeed(Any one, Any two) { 
  Brain.Screen.clearLine(1);
  Brain.Screen.clearScreen();
  Brain.Screen.print(two); 
  Brain.Screen.print("  "); 
  Brain.Screen.print(one); 
  return 0; 
}

void MoveMotors(int pos, int pos2) {
  int a = ABS(pos2)*MOVING_MULTIPLIER;
  int a2 = ABS(pos)*MOVING_MULTIPLIER;

  if (pos == 0 && pos2 == 0) {
    Motor1.stop();
    Motor2.stop();
    Motor3.stop();
    Motor4.stop();
  }

  printSpeed(pos*MOVING_MULTIPLIER, pos2*MOVING_MULTIPLIER);

  Motor1.setVelocity(a, rpm);
  Motor1.spin(pos < 0 ? forward : reverse);
  Motor2.setVelocity(a, rpm);
  Motor2.spin(pos < 0 ? forward : reverse);
  Motor3.setVelocity(a2, rpm);
  Motor3.spin(pos2 < 0 ? reverse : forward);
  Motor4.setVelocity(a2, rpm);
  Motor4.spin(pos2 < 0 ? reverse : forward);
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

void initStearing() {
  Motor1.setStopping(coast);
  Motor2.setStopping(coast);
  Motor3.setStopping(coast);
  Motor4.setStopping(coast);
  Controller1.Axis3.changed(assessMovement);
  Controller1.Axis4.changed(assessMovement);
}
int main() {
  initStearing();
}
