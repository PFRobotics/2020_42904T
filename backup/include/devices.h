#include "vex.h"
using namespace vex;

vex::controller controller1 = vex::controller();

//Drive Motors
vex::motor motorFrontLeft = vex::motor(PORT8, gearSetting::ratio18_1, true);
vex::motor motorFrontRight = vex::motor(PORT7, gearSetting::ratio18_1, false);
vex::motor motorBackLeft = vex::motor(PORT4, gearSetting::ratio18_1, true);
vex::motor motorBackRight = vex::motor(PORT6, gearSetting::ratio18_1, false);