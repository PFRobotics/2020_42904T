#include "vex.h"
using namespace vex;

controller controller1 = controller();

//Drive Motors
motor motorFrontLeft = motor(PORT19, gearSetting::ratio18_1, true);
motor motorFrontRight = motor(PORT9, gearSetting::ratio18_1, false);
motor motorBackLeft = motor(PORT18, gearSetting::ratio18_1, true);
motor motorBackRight = motor(PORT10, gearSetting::ratio18_1, false);

motor motorTray = motor(PORT20, gearSetting::ratio18_1, true);

motor motorLift = motor(PORT15, gearSetting::ratio36_1, false);

motor motorLeftIntake = motor(PORT17, gearSetting::ratio18_1, true);
motor motorRightIntake = motor(PORT8, gearSetting::ratio18_1, false);