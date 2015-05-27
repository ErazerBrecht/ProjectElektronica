/*
  Robot.cpp - Library for TB6612FNG
  Created by Brecht Carlier & Arne Schoonvliet, October 8, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Robot.h"

Robot::Robot(int pinForwardLeft, int pinReverseLeft, int pinPWMLeft, int pinForwardRight, int pinReverseRight, int pinPWMRight)
{
  pinMode(pinForwardLeft, OUTPUT);
  pinMode(pinReverseLeft, OUTPUT);
  pinMode(pinPWMLeft, OUTPUT);

  pinMode(pinForwardRight, OUTPUT);
  pinMode(pinReverseRight, OUTPUT);
  pinMode(pinPWMRight, OUTPUT);


  _pinForwardLeft = pinForwardLeft;
  _pinReverseLeft = pinReverseLeft; 
  _pinPWMLeft = pinPWMLeft;

  _pinForwardRight = pinForwardRight;
  _pinReverseRight = pinReverseRight;
  _pinPWMRight = pinPWMRight;
 
}

void Robot::Forward(int Speed)
{
  MotorForward(_pinForwardLeft,_pinReverseLeft, _pinPWMLeft, Speed);	//Motor Left Forward
  MotorForward(_pinForwardRight,_pinReverseRight, _pinPWMRight, Speed);	//Motor Right Forward
}

void Robot::Reverse(int Speed)
{
  MotorReverse(_pinForwardLeft,_pinReverseLeft, _pinPWMLeft, Speed);	//Motor Left Forward
  MotorReverse(_pinForwardRight,_pinReverseRight, _pinPWMRight, Speed);	//Motor Right Forward
}

//We maken gebruik van twee verschillende PWM's zo kunnen we variabele sturen!
void Robot::Turn(int SpeedRight, int SpeedLeft)	
{
	//Motor Right
	//Check if motors have to go reverse
	if (SpeedRight > 0)			
		MotorForward(_pinForwardRight,_pinReverseRight, _pinPWMRight, SpeedRight);			//Motor Right Forward
	else
		MotorReverse(_pinForwardRight,_pinReverseRight, _pinPWMRight, SpeedRight * -1);		//Motor Right Reverse Convert negative PWM to positive PWM
  
	//Motor Left
	//Check if motors have to go reverse
	if (SpeedLeft > 0) //Check if motors have to go reverse
		MotorForward(_pinForwardLeft, _pinReverseLeft, _pinPWMLeft, SpeedLeft);				//Motor Left Forward
	else
		MotorReverse(_pinForwardLeft, _pinReverseLeft, _pinPWMLeft, SpeedLeft * -1);		//Motor Left Reverse Convert negative PWM to positive PWM
  
}

void Robot::Stop()
{
 MotorStop(_pinForwardLeft,_pinReverseLeft);		
 MotorStop(_pinForwardRight,_pinReverseRight);		
}

void Robot::MotorForward(int pinForward, int pinReverse, int pinPWM, int Speed)
{
  analogWrite(pinPWM, Speed);
  digitalWrite(pinForward, HIGH);
  digitalWrite(pinReverse, LOW);
}

void Robot::MotorReverse(int pinForward, int pinReverse, int pinPWM, int Speed)
{
  analogWrite(pinPWM, Speed);
  digitalWrite(pinForward, LOW);
  digitalWrite(pinReverse, HIGH);
}

void Robot::MotorStop(int pinForward, int pinReverse)
{
  digitalWrite(pinForward, HIGH);
  digitalWrite(pinReverse, HIGH);
}