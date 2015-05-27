/*
Library for Project Elektronica
Ultrasoon.h - Library for HC-SR04
Created by Brecht Carlier & Arne Schoonvliet
*/

#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include "Ultrasoon.h"

class Sensor
{
public:
	Sensor(int pin);
	Sensor(int pin, int pin2);
	bool isCloser(int x);
	bool isCloser(int sensornumer, int x);
	bool bothCloser(int x);
	int calculateTurnDirection();		//Check wich sensor has the most place... If sensor right has more place turn right!
	//TODO: Should become an array!
	Ultrasoon Ultra[2];
	
private:
	int _pin;
	int _pin2;
	bool _double;

};

#endif