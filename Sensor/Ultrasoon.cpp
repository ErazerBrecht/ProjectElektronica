/*
Library for Project Elektronica
Ultrasoon.cpp - Library for HC-SR04
Created by Brecht Carlier & Arne Schoonvliet
*/

#include "Arduino.h"
#include "Ultrasoon.h"

//Constructor
Ultrasoon::Ultrasoon(int trigPin, int echoPin)
{
	_trigPin = trigPin;		//Save the constuctor parameter (pin) to a private field (is used later for measuring)
	_echoPin = echoPin;

	Filter.begin();			//Start the filter library
	Filter.setFilter('m');  //Set it's mode on "median" 
	Filter.setOrder(3);		//Set the number of sample the filter uses to calculate the median!

	pinMode(_trigPin, OUTPUT);
	pinMode(_echoPin, INPUT);
}

//Private!
//The main function of this library
//This function will do the measuring!
long Ultrasoon::getCentimeter()
{
	// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(_trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(_trigPin, HIGH);
	delayMicroseconds(10);

	digitalWrite(_trigPin, LOW);
	_duration = pulseIn(_echoPin, HIGH);

	//Calculate the distance (in cm) and filter against fault readings!
	_filteredDistance = Filter.run(_duration / 58.2);

	//Check if sensor value is out of range!
	if (_filteredDistance < 2)
	{
		_filteredDistance = 1;
	}

	//Check if sensor value is out of range!
	else if (_filteredDistance > 400)
	{
		_filteredDistance = 401;
	}

	delay(50);

	//Return the distance value
	return _filteredDistance;

}

//Function to check if the sensor is closer then x cm
//If this is the case return true otherwise return false!
bool Ultrasoon::isCloser(int x)
{
	getCentimeter();
	if (_filteredDistance < x)
	{
		return true;
	}
	else{
		return false;
	}
}