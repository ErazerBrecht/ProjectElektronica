/*
  Library for Lab Microcontrollers
  Sharp.h - Library for GP2Y0A41SK0F
  Created by Brecht Carlier
*/

#ifndef Ultrasoon_h
#define Ultrasoon_h

#include "Arduino.h"
#include "SignalFilter.h"

class Ultrasoon
{
  public:
    Ultrasoon(int trigPin, int echoPin);
	void printSerialDistance();
    float getCentimeter();
	bool isCloser(int x);

  private:
    int _trigPin;
	int _echoPin;
    SignalFilter Filter;
	long _duration;
	long _filtered;
	long _distance;
};

#endif