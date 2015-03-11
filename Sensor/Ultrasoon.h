/*
  Library for Project Elektronica
  Ultrasoon.h - Library for HC-SR04
  Created by Brecht Carlier & Arne Schoonvliet
*/

#ifndef Ultrasoon_h
#define Ultrasoon_h

#include "Arduino.h"
#include "SignalFilter.h"

class Ultrasoon
{
  public:
    Ultrasoon(int trigPin, int echoPin); 
	Ultrasoon(int trigPin, int echoPin, int trigPin2, int echoPin2);
	bool isCloser(int x);

  private:
    int _trigPin;
	int _echoPin;
	int _trigPin2;
	int _echoPin2;

	bool _fusion;
    
	SignalFilter Filter;
	
	long _duration;
	long _filteredDistance;
	long _centimeter;		//TODO: Needs to become an array!
	long _centimeter2;

	void getCentimeter();
	void getCentimeterFusion();
	long calculateCentimeter(int trigPin, int echoPin);
};

#endif