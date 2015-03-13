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
<<<<<<< HEAD:Sensor/Ultrasoon.h
    Ultrasoon(int trigPin, int echoPin); 
	Ultrasoon(int trigPin, int echoPin, int trigPin2, int echoPin2);
=======
    void begin(int trigPin, int echoPin); 
>>>>>>> NewOO:RobotArduino/Ultrasoon.h
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
<<<<<<< HEAD:Sensor/Ultrasoon.h
	long _centimeter;		//TODO: Needs to become an array!
	long _centimeter2;

	void getCentimeter();
	void getCentimeterFusion();
	long calculateCentimeter(int trigPin, int echoPin);
=======
	void getCentimeter();
>>>>>>> NewOO:RobotArduino/Ultrasoon.h
};

#endif