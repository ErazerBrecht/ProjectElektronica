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
    void begin(int pin); 
	bool isCloser(int x);
	int getCentimeter();
	int _filteredDistance;

  private:
    int _pin;
    SignalFilter Filter;
	int _value;
	int _filtered;
	
};

#endif