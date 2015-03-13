/*
Library for Project Elektronica
Ultrasoon.cpp - Library for HC-SR04
Created by Brecht Carlier & Arne Schoonvliet
*/

#include "Arduino.h"
#include "Ultrasoon.h"

//Constructor
<<<<<<< HEAD:Sensor/Ultrasoon.cpp
//We have two constructors
//One accepts 2 pins (one sensor)
//Another accepts 4 pins (two sensor)
//The Library is made with native support to fuse two sensors. As example: you could use two forward sensors for big robots. Arduino will see it as one!
//Conclusion: The Arduino program will not change!!!
//TODO: Filter init in seperate method
Ultrasoon::Ultrasoon(int trigPin, int echoPin)
=======
void Ultrasoon::begin(int trigPin, int echoPin)
>>>>>>> NewOO:RobotArduino/Ultrasoon.cpp
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
	_trigPin2 = trigPin2;		
	_echoPin2 = echoPin2;

	//TODO: Make Filter init function!
	Filter.begin();			//Start the filter library
	Filter.setFilter('m');  //Set it's mode on "median" 
	Filter.setOrder(3);		//Set the number of sample the filter uses to calculate the median!

	pinMode(_trigPin, OUTPUT);
	pinMode(_echoPin, INPUT);
	pinMode(_trigPin2, OUTPUT);
	pinMode(_echoPin2, INPUT);
}

//Private!
//The main function of this library
<<<<<<< HEAD:Sensor/Ultrasoon.cpp
//This function will do the actual measuring!
long Ultrasoon::calculateCentimeter(int trigPin, int echoPin)
=======
//This function will do the measuring!
void Ultrasoon::getCentimeter()
>>>>>>> NewOO:RobotArduino/Ultrasoon.cpp
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

	//Check if sensor value is out of range!
	if (_filteredDistance < 3)
	{
		_filteredDistance = 2;
	}

	//Check if sensor value is out of range!
	else if (_filteredDistance > 400)
	{
		_filteredDistance = 401;
	}

	return _filteredDistance;

}

//Two private functions that add the stability delay
//With the fusion method we will return the smallest value.
//This value is closer to wall and is thus more important! 
void Ultrasoon::getCentimeter()
{
	_centimeter = calculateCentimeter(_trigPin, _echoPin);
	delay(25);
<<<<<<< HEAD:Sensor/Ultrasoon.cpp
}

void Ultrasoon::getCentimeterFusion()
{
	_centimeter = calculateCentimeter(_trigPin, _echoPin);
	delay(25);
	_centimeter2 = calculateCentimeter(_trigPin2, _echoPin2);
	delay(25);

	if (_centimeter2 < _centimeter)
		_centimeter = _centimeter2;
=======
>>>>>>> NewOO:RobotArduino/Ultrasoon.cpp
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