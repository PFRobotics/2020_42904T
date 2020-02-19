/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\aiden                                            */
/*    Created:      Tue Sep 10 2019                                           */
/*    Description:  V5 project                                                */
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

// define your global instances of motors and other devices here

int main() {
    while(true) {
        if(controller1.Axis3.value() > 0){
          double A3 = controller1.Axis3.value();
          double A4 = controller1.Axis4.value();
          motorFrontLeft.spin(directionType::fwd, (A3 > A4)? LIB::ConvertJoyToMotor(A3) : LIB::ConvertJoyToMotor(A4), percentUnits::pct);
          motorFrontRight.spin(directionType::fwd, (A3 > A4)? LIB::ConvertJoyToMotor(A3) : LIB::ConvertJoyToMotor(A4), percentUnits::pct);
          motorBackLeft.spin(directionType::fwd, (A3 > A4)? LIB::ConvertJoyToMotor(A3) : LIB::ConvertJoyToMotor(A4), percentUnits::pct);
          motorBackRight.spin(directionType::fwd, (A3 > A4)? LIB::ConvertJoyToMotor(A3) : LIB::ConvertJoyToMotor(A4), percentUnits::pct);
        }
        else if(controller1.Axis3.value() < 0){
          double A3 = std::abs(controller1.Axis3.value());
          double A4 = std::abs(controller1.Axis4.value());
          motorFrontLeft.spin(directionType::rev, (A3 < A4)? LIB::ConvertJoyToMotor(A4) : LIB::ConvertJoyToMotor(A3), percentUnits::pct);
          motorFrontRight.spin(directionType::rev, (A3 < A4)? LIB::ConvertJoyToMotor(A4) : LIB::ConvertJoyToMotor(A3), percentUnits::pct);
          motorBackLeft.spin(directionType::rev, (A3 < A4)? LIB::ConvertJoyToMotor(A4) : LIB::ConvertJoyToMotor(A3), percentUnits::pct);
          motorBackRight.spin(directionType::rev, (A3 < A4)? LIB::ConvertJoyToMotor(A4) : LIB::ConvertJoyToMotor(A3), percentUnits::pct);
        }

        if(controller1.Axis4.value() > 0){
          double A3 = controller1.Axis3.value();
          double A4 = controller1.Axis4.value();
          motorFrontRight.spin(directionType::rev, (A4 > A3)? LIB::ConvertJoyToMotor(A4) : LIB::ConvertJoyToMotor(A3), percentUnits::pct);
          motorBackRight.spin(directionType::fwd, (A4 > A3)? LIB::ConvertJoyToMotor(A4) : LIB::ConvertJoyToMotor(A3), percentUnits::pct);
          motorFrontLeft.spin(directionType::fwd, (A4 > A3)? LIB::ConvertJoyToMotor(A4) : LIB::ConvertJoyToMotor(A3), percentUnits::pct);
          motorBackLeft.spin(directionType::rev, (A4 > A3)? LIB::ConvertJoyToMotor(A4) : LIB::ConvertJoyToMotor(A3), percentUnits::pct);
        }
        else if(controller1.Axis4.value() < 0){
          double A3 = std::abs(controller1.Axis3.value());
          double A4 = std::abs(controller1.Axis4.value());
          motorFrontRight.spin(directionType::fwd, (A4 < A3)? LIB::ConvertJoyToMotor(A3) : LIB::ConvertJoyToMotor(A4), percentUnits::pct);
          motorBackRight.spin(directionType::rev, (A4 < A3)? LIB::ConvertJoyToMotor(A3) : LIB::ConvertJoyToMotor(A4), percentUnits::pct);
          motorFrontLeft.spin(directionType::rev, (A4 < A3)? LIB::ConvertJoyToMotor(A3) : LIB::ConvertJoyToMotor(A4), percentUnits::pct);
          motorBackLeft.spin(directionType::fwd, (A4 < A3)? LIB::ConvertJoyToMotor(A3) : LIB::ConvertJoyToMotor(A4), percentUnits::pct);
        }

        if(controller1.Axis1.value() > 0){
          motorFrontLeft.spin(directionType::rev, LIB::ConvertJoyToMotor(controller1.Axis1.value()), percentUnits::pct);
          motorFrontRight.spin(directionType::fwd, LIB::ConvertJoyToMotor(controller1.Axis1.value()), percentUnits::pct);
          motorBackRight.spin(directionType::fwd, LIB::ConvertJoyToMotor(controller1.Axis1.value()), percentUnits::pct);
          motorBackLeft.spin(directionType::rev, LIB::ConvertJoyToMotor(controller1.Axis1.value()), percentUnits::pct);
        }
        else if(controller1.Axis1.value() < 0){
          motorFrontLeft.spin(directionType::fwd, LIB::ConvertJoyToMotor(std::abs(controller1.Axis1.value())), percentUnits::pct);
          motorFrontRight.spin(directionType::rev, LIB::ConvertJoyToMotor(std::abs(controller1.Axis1.value())), percentUnits::pct);
          motorBackRight.spin(directionType::rev, LIB::ConvertJoyToMotor(std::abs(controller1.Axis1.value())), percentUnits::pct);
          motorBackLeft.spin(directionType::fwd, LIB::ConvertJoyToMotor(std::abs(controller1.Axis1.value())), percentUnits::pct);
        }

        if(controller1.Axis3.value() == 0 && controller1.Axis4.value() == 0 && controller1.Axis1.value() == 0){
          motorFrontLeft.stop(brakeType::coast);
          motorFrontRight.stop(brakeType::coast);
          motorBackRight.stop(brakeType::coast);
          motorBackLeft.stop(brakeType::coast);
        }

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

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
