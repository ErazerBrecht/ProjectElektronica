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
	Sensor(int trigPin, int pinEcho);
	Sensor(int trigPin, int pinEcho, int trigPin2, int pinEcho2);
	bool isCloser(int x);
	bool isFarDual();		//Check wich sensor has the most place...

	//TODO: Change names!
	Ultrasoon _ultraOne;
	Ultrasoon _ultraTwo;

private:
	int _trigPin;
	int _echoPin;
	int _trigPin2;
	int _echoPin2;
	bool _double;

	//Should become an array!
};

#endif