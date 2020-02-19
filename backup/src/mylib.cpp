#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>
#include "mylib.h"

using namespace std;

namespace LIB
{ 
    int Clamp(int max, int min, int value){
      if(value > max){
        return max;
      }
      else if(value < min){
        return min;
      }
      else{
        return value;
      }
    }
    
    int ConvertJoyToMotor(double joystickPos){
      //Scale 0 to 12 -> 0 to 10
      double rescaledJoy  = joystickPos * 0.7874015748031496;
      int roundedValue = round(rescaledJoy);
      return Clamp(100, 0, roundedValue);
    }
}