/*
  Ultrasoon.cpp - Library for GP2Y0A41SK0F
  Created by Brecht Carlier
  */

#include "Arduino.h"
#include "Ultrasoon.h"

//Constructor
Ultrasoon::Ultrasoon(int trigPin, int echoPin)
{
	_trigPin = trigPin;		//Save the constuctor parameter to private field (is used later for analogRead)
	_echoPin = echoPin;
	Filter.begin();			//Start the filter library
	Filter.setFilter('m');    //Set it's mode on "median" 
	Filter.setOrder(3);		//Set the number of sample the filter uses to calculate the median!

	pinMode(_trigPin, OUTPUT);
	pinMode(_echoPin, INPUT);

}

//Function to print the distance trough the serial interface!
void Ultrasoon::printSerialDistance()
{
	getCentimeter();
	Serial.println(_filtered);
}


//The main function of this library
//This function will do the measuring!
float Ultrasoon::getCentimeter()
{
	// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(_trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(_trigPin, HIGH);
	delayMicroseconds(10);

	digitalWrite(_trigPin, LOW);
	_duration = pulseIn(_echoPin, HIGH);

	//Calculate the distance (in cm).
	_distance = _duration / 58.2;
	_filtered = Filter.run(_distance);					//Filter against fault readings!

	//Check if sensor value is out of range!
	if (_filtered < 2)
	{
		_filtered = 1;
	}

	//Check if sensor value is out of range!
	else if (_filtered > 400)
	{
		_filtered = 401;
	}

	//Return the distance value
	return _filtered;

}

//Function to check if the sensor is closer then x cm
//If this is the case return true otherwise return false!
bool Ultrasoon::isCloser(int x)
{
	if (_distance < x)
	{
		return true;
	}
	else{
		return false;
	}
}