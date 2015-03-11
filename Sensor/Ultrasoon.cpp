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
	_fusion = false;

	_trigPin = trigPin;		//Save the constuctor parameter (pin) to a private field (is used later for measuring)
	_echoPin = echoPin;

	Filter.begin();			//Start the filter library
	Filter.setFilter('m');  //Set it's mode on "median" 
	Filter.setOrder(3);		//Set the number of sample the filter uses to calculate the median!

	pinMode(_trigPin, OUTPUT);
	pinMode(_echoPin, INPUT);
}

Ultrasoon::Ultrasoon(int trigPin, int echoPin, int trigPin2, int echoPin2)
{
	_fusion = true;

	_trigPin = trigPin;		//Save the constuctor parameter (pin) to a private field (is used later for measuring)
	_echoPin = echoPin;
	_trigPin2 = trigPin2;		//Save the constuctor parameter (pin) to a private field (is used later for measuring)
	_echoPin2 = echoPin2;

	Filter.begin();			//Start the filter library
	Filter.setFilter('m');  //Set it's mode on "median" 
	Filter.setOrder(3);		//Set the number of sample the filter uses to calculate the median!

	pinMode(_trigPin, OUTPUT);
	pinMode(_echoPin, INPUT);
	pinMode(_trigPin2, OUTPUT);
	pinMode(_echoPin2, INPUT);
}
//Private!
long Ultrasoon::calculateCentimeter(int trigPin, int echoPin)
{
	// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPin, LOW);
	_duration = pulseIn(echoPin, HIGH);

	//Calculate the distance (in cm) and filter against fault readings!
	_filteredDistance = Filter.run(_duration / 58.2);

	//_filteredDistance = _duration / 58.2;

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

	return _filteredDistance;

}


//Private!
//The main function of this library
//This function will do the measuring!
long Ultrasoon::getCentimeter()
{
	_centimeter = calculateCentimeter(_trigPin, _echoPin);
	delay(25);

	//Return the distance value
	return _centimeter;
}

long Ultrasoon::getCentimeterFusion()
{
	_centimeter = calculateCentimeter(_trigPin, _echoPin);
	delay(25);
	_centimeter2 = calculateCentimeter(_trigPin2, _echoPin2);
	delay(25);

	if (_centimeter2 < _centimeter)
		_centimeter = _centimeter2
}



//First measure distance with private function (getCentimeter)
//Function to check if the sensor is closer then x cm
//If this is the case return true otherwise return false!
bool Ultrasoon::isCloser(int x)
{
	if (_fusion == false)
		getCentimeter();
	else
		getCentimeterFusion();

	if (_centimeter < x)
	{
		return true;
	}
	else{
		return false;
	}
}