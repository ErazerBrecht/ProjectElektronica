/*
Library for Project Elektronica
Ultrasoon.cpp - Library for HC-SR04
Created by Brecht Carlier & Arne Schoonvliet
*/

#include "Arduino.h"
#include "Ultrasoon.h"

//Constructor
void Ultrasoon::begin(int pin)
{
	_pin = pin;		//Save the constuctor parameter (pin) to a private field (is used later for measuring)

	//TODO: Make Filter init function!
	//Filter.begin();			//Start the filter library
	//Filter.setFilter('m');  //Set it's mode on "median" 
	//Filter.setOrder(3);		//Set the number of sample the filter uses to calculate the median!
}

//Private!
//The main function of this library
//This function will do the measuring!
int Ultrasoon::getCentimeter()
{
	_value = analogRead(_pin);							//Read the voltage from the sensor with the ADC from the microcontroller!
	//_filtered = Filter.run(_value);					//Filter against fault readings!
	_filteredDistance = 3616.7 * pow(_value, -1.07);	//Equation to calculate centimeters

	//Check if sensor value is out of range!
	if (_filteredDistance < 4)
	{
		_filteredDistance = 3;
	}

	//Check if sensor value is out of range!
	else if (_filteredDistance > 30)
	{
		_filteredDistance = 31;
	}

	//Return the distance value
	return _filteredDistance;
}

//First measure distance with private function (getCentimeter)
//Function to check if the sensor is closer then x cm
//If this is the case return true otherwise return false!
bool Ultrasoon::isCloser(int x)
{
	getCentimeter();
	//Serial.print("Afstand: ");
	//Serial.println(_filteredDistance);
	if (_filteredDistance < x)
	{
		return true;
	}
	else{
		return false;
	}
}