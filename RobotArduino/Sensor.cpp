#include "Sensor.h"

Sensor::Sensor(int trigPin, int echoPin)
{
     Ultra[0].begin(trigPin, echoPin);
	 _double = false;
}

Sensor::Sensor(int trigPin, int echoPin, int trigPin2, int echoPin2)
{
	Ultra[0].begin(trigPin, echoPin);
	Ultra[1].begin(trigPin2, echoPin2);
	_double = true;
}

bool Sensor::isCloser(int x)
{
	if (!_double)
		return Ultra[0].isCloser(x);
	
	else
	{
		/*
		Serial.print("Afstand sensor 1: ");
		Serial.println(Ultra[0]._filteredDistance);
		Serial.print("Afstand sensor 2: ");
		Serial.println(Ultra[1]._filteredDistance);
		*/
		if (Ultra[0].isCloser(x) || Ultra[1].isCloser(x))
		{
			return true;
		}
		else
			return false;
	}
}

bool Sensor::isCloser(int sensornumer, int x)
{
	if (_double)
	{
		if (Ultra[sensornumer].isCloser(x))
			return true;
		else
			return false;
	}
	return false;
}

bool Sensor::bothCloser(int x)
{
	if (_double)
	{
		if (Ultra[0].isCloser(x) && Ultra[1].isCloser(x))
			return true;
		else
			return false;
	}
	return false;
}

int Sensor::calculateTurnDirection()
{
	//If one of the sides distance is lower than 20 decide to not turn to that direction
	//Otherwise choose random (this is done to escape a square)
	long centimeterZero = Ultra[0].getCentimeter();
	long centimeterOne = Ultra[1].getCentimeter();

	if (centimeterZero < 20 || centimeterOne < 20)
	{
		if (centimeterZero > centimeterOne)
		{
			return 0;
		}

		return 1;
	}

	else return random(0, 2);
}



