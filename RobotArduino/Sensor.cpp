#include "Sensor.h"

Sensor::Sensor(int pin)
{
     Ultra[0].begin(pin);
	 _double = false;
}

Sensor::Sensor(int pin, int pin2)
{
	Ultra[0].begin(pin);
	Ultra[1].begin(pin2);
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
	int centimeterZero = Ultra[0].getCentimeter();
	int centimeterOne = Ultra[1].getCentimeter();

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



