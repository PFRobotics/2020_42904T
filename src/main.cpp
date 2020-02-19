/*----------------------------------------------------------------------------*/ 
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Copyright Aiden Wilkins                                   */
/*    Created:      Tue Sep 10 2019                                           */
/*    Description:  X-Drive Code                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_motor.h"
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
#include "vex.h"
#include "devices.h"
#include "mylib.h"
#include <cmath>

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain  Brain;
vex::competition Competition;

// define your global instances of motors and other devices here
void man(){
  while(true) {
    
    // X-Drive Begin
    double A = controller1.Axis3.value();
    double B = controller1.Axis4.value();
    double C = controller1.Axis1.value();
    if(A != 0 || B != 0 || C != 0){
      motorFrontLeft.spin((A + B + C) < 0? directionType::fwd : directionType::rev, std::abs(A + B + C), percentUnits::pct);
      motorBackLeft.spin((A - B + C) < 0? directionType::fwd : directionType::rev, std::abs(A - B + C), percentUnits::pct);

      motorFrontRight.spin(((-A) + B + C) < 0? directionType::rev : directionType::fwd, std::abs((-A) + B + C), percentUnits::pct);
      motorBackRight.spin(((-A) - B + C) < 0? directionType::rev : directionType::fwd, std::abs((-A) - B + C), percentUnits::pct);
    }
    else{
      motorFrontLeft.stop();
      motorFrontRight.stop();
      motorBackLeft.stop();
      motorBackRight.stop();
    }
    // X-Drive End

    // Tray Controlls
    if(controller1.ButtonX.pressing() && motorTray.rotation(rotationUnits::deg) < 1300){
      if(motorTray.rotation(rotationUnits::deg) < 1000)
        motorTray.spin(directionType::fwd, 50, percentUnits::pct);
      else if(motorTray.rotation(rotationUnits::deg) > 1000)
        motorTray.spin(directionType::fwd, 20, percentUnits::pct);
      else if(motorTray.rotation(rotationUnits::deg) > 1115)
        motorTray.spin(directionType::fwd, 5, percentUnits::pct);
    }
    else if(controller1.ButtonA.pressing() && motorTray.rotation(rotationUnits::deg) > 0){
      motorTray.spin(directionType::rev, 50, percentUnits::pct);
    }
    else if(controller1.ButtonB.pressing()){
      motorTray.spin(directionType::rev, 50, percentUnits::pct);
    }
    else{
      motorTray.stop(brakeType::hold);
    }

    //Arm Controls
    if(controller1.ButtonL1.pressing()){
      motorLift.spin(directionType::fwd, 50, percentUnits::pct);
    }
    else if(controller1.ButtonL2.pressing()){
      motorLift.spin(directionType::rev, 50, percentUnits::pct);
    }
    else{
      motorLift.stop(brakeType::hold);
    }

    //Intake Controls
    if(controller1.ButtonR1.pressing()){
      motorLeftIntake.spin(directionType::rev, 100, percentUnits::pct);
      motorRightIntake.spin(directionType::rev, 100, percentUnits::pct);
    }
    else if(controller1.ButtonR2.pressing()){
      motorLeftIntake.spin(directionType::fwd, 75, percentUnits::pct);
      motorRightIntake.spin(directionType::fwd, 75, percentUnits::pct);
    }
    else{
      motorRightIntake.stop();
      motorLeftIntake.stop();
    }

    //More Random Debug Stuff
    Brain.Screen.printAt(10,  150, "Axis1 %.2f", (float)LIB::ConvertJoyToMotor(controller1.Axis1.value()));
    Brain.Screen.printAt(10,  110, "Axis3 %.2f", (float)LIB::ConvertJoyToMotor(controller1.Axis3.value()));
    Brain.Screen.printAt(10,  130, "Axis4 %.2f", (float)LIB::ConvertJoyToMotor(controller1.Axis4.value()));

    Brain.Screen.printAt(10, 30, "Front Left %.2f %.2f %.2f %.2f", motorFrontLeft.velocity(velocityUnits::rpm), motorFrontLeft.current(currentUnits::amp), 
    motorFrontLeft.temperature(temperatureUnits::celsius), motorFrontLeft.torque(torqueUnits::Nm));
    Brain.Screen.printAt(10, 50, "Front Right %.2f %.2f %.2f %.2f", motorFrontRight.velocity(velocityUnits::rpm), motorFrontRight.current(currentUnits::amp), 
    motorFrontRight.temperature(temperatureUnits::celsius), motorFrontRight.torque(torqueUnits::Nm));
    Brain.Screen.printAt(10, 70, "Back Left %.2f %.2f %.2f %.2f", motorBackLeft.velocity(velocityUnits::rpm), motorBackLeft.current(currentUnits::amp), 
    motorBackLeft.temperature(temperatureUnits::celsius), motorBackLeft.torque(torqueUnits::Nm));
    Brain.Screen.printAt(10, 90, "Back Right %.2f %.2f %.2f %.2f", motorBackRight.velocity(velocityUnits::rpm), motorBackRight.current(currentUnits::amp), 
    motorBackRight.temperature(temperatureUnits::celsius), motorBackRight.torque(torqueUnits::Nm));
    Brain.Screen.printAt(10, 150, "Tray Rotation %.2f", motorTray.rotation(rotationUnits::deg));
    Brain.Screen.printAt(10, 170, "Motor Rotation %.2f", motorBackRight.rotation(rotationUnits::rev));

    // Allow other tasks to run, NO U
    this_thread::sleep_for(10);
  }
}

double RTD(double d){
  return d / 25.9207;
}

double RTR(double r){
  return (r * 0.0155555555555556);
}

void f(double distance, double velocity){
  motorFrontLeft.setVelocity(velocity, percentUnits::pct);
  motorFrontRight.setVelocity(velocity, percentUnits::pct);
  motorBackLeft.setVelocity(velocity, percentUnits::pct);
  motorBackRight.setVelocity(velocity, percentUnits::pct);
  
  motorFrontLeft.rotateFor(directionType::rev, RTD(distance), rotationUnits::rev, false);
  motorFrontRight.rotateFor(directionType::rev, RTD(distance), rotationUnits::rev, false);
  motorBackLeft.rotateFor(directionType::rev, RTD(distance), rotationUnits::rev, false);
  motorBackRight.rotateFor(directionType::rev, RTD(distance), rotationUnits::rev);
}

void b(double distance, double velocity){
  motorFrontLeft.setVelocity(velocity, percentUnits::pct);
  motorFrontRight.setVelocity(velocity, percentUnits::pct);
  motorBackLeft.setVelocity(velocity, percentUnits::pct);
  motorBackRight.setVelocity(velocity, percentUnits::pct);

  motorFrontLeft.rotateFor(directionType::fwd, RTD(distance), rotationUnits::rev, false);
  motorFrontRight.rotateFor(directionType::fwd, RTD(distance), rotationUnits::rev, false);
  motorBackLeft.rotateFor(directionType::fwd, RTD(distance), rotationUnits::rev, false);
  motorBackRight.rotateFor(directionType::fwd, RTD(distance), rotationUnits::rev);
}

void s_l(double distance, double velocity){
  motorFrontLeft.setVelocity(velocity, percentUnits::pct);
  motorFrontRight.setVelocity(velocity, percentUnits::pct);
  motorBackLeft.setVelocity(velocity, percentUnits::pct);
  motorBackRight.setVelocity(velocity, percentUnits::pct);

  motorFrontLeft.rotateFor(directionType::fwd, RTD(distance), rotationUnits::rev, false);
  motorFrontRight.rotateFor(directionType::rev, RTD(distance), rotationUnits::rev, false);
  motorBackLeft.rotateFor(directionType::rev, RTD(distance), rotationUnits::rev, false);
  motorBackRight.rotateFor(directionType::fwd, RTD(distance), rotationUnits::rev);
}

void t_l(double rotation, double velocity){
  motorFrontLeft.setVelocity(velocity, percentUnits::pct);
  motorFrontRight.setVelocity(velocity, percentUnits::pct);
  motorBackLeft.setVelocity(velocity, percentUnits::pct);
  motorBackRight.setVelocity(velocity, percentUnits::pct);

  motorFrontLeft.rotateFor(directionType::fwd, rotation, rotationUnits::rev, false);
  motorFrontRight.rotateFor(directionType::rev, rotation, rotationUnits::rev, false);
  motorBackLeft.rotateFor(directionType::fwd, rotation, rotationUnits::rev, false);
  motorBackRight.rotateFor(directionType::rev, rotation, rotationUnits::rev);
}

void t_r(double rotation, double velocity){
  motorFrontLeft.setVelocity(velocity, percentUnits::pct);
  motorFrontRight.setVelocity(velocity, percentUnits::pct);
  motorBackLeft.setVelocity(velocity, percentUnits::pct);
  motorBackRight.setVelocity(velocity, percentUnits::pct);

  motorFrontLeft.rotateFor(directionType::rev, rotation, rotationUnits::rev, false);
  motorFrontRight.rotateFor(directionType::fwd, rotation, rotationUnits::rev, false);
  motorBackLeft.rotateFor(directionType::rev, rotation, rotationUnits::rev, false);
  motorBackRight.rotateFor(directionType::fwd, rotation, rotationUnits::rev);
}

void auton(){

  //t_l(RTR(135), 100);

  // Open tray
  f(5, 100);
  motorLeftIntake.setVelocity(100, percentUnits::pct);
  motorRightIntake.setVelocity(100, percentUnits::pct);
  motorTray.setVelocity(75, percentUnits::pct);

  motorLeftIntake.spin(directionType::fwd);
  motorRightIntake.spin(directionType::fwd);

  motorTray.rotateFor(directionType::fwd, 1260, rotationUnits::deg);
  task::sleep(1000);

  b(4, 50);
  motorTray.rotateTo(0, rotationUnits::deg);

  motorLeftIntake.spin(directionType::rev);
  motorRightIntake.spin(directionType::rev);

  f(65, 35);

  task::sleep(1750);

  motorLeftIntake.stop();
  motorRightIntake.stop();
}

int main() {
  Competition.autonomous(auton);
  Competition.drivercontrol(man);
  //man();
}
