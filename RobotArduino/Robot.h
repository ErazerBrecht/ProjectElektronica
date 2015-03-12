/*
  Robot.h - Library for TB6612FNG
  Created by Brecht Carlier & Arne Schoonvliet, October 8, 2014.
  Released into the public domain. 
  GPL licensed
*/
#ifndef Robot_h
#define Robot_h

#include "Arduino.h"

class Robot
{
  public:
    Robot(int pinForwardLeft, int pinReverseLeft, int pinPWMLeft, int pinForwardRight, int pinReverseRight, int pinPWMRight);
    void Forward(int Speed);
    void Reverse(int Speed);
    void Left(int SpeedRight, int SpeedLeft);
    void Right(int SpeedRight, int SpeedLeft);
    void Stop();

	//int Speed;
	
  private:
    int _pinForwardLeft;
    int _pinReverseLeft;
	int _pinPWMLeft;

    int _pinForwardRight;
    int _pinReverseRight;
	int _pinPWMRight;

	/*int _speedLeft;
	int _speedRight;*/

    
    void MotorForward(int pinForward, int pinReverse, int pinPWM, int Speed);
    void MotorReverse(int pinForward, int pinReverse, int pinPWM, int Speed);
    void MotorStop(int pinForward, int pinReverse);

};

#endif