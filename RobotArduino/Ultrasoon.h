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
    void begin(int trigPin, int echoPin); 
	bool isCloser(int x);
	long getCentimeter();
	long _filteredDistance;

  private:
    int _trigPin;
	int _echoPin;
    SignalFilter Filter;
	long _duration;
	
};

#endif