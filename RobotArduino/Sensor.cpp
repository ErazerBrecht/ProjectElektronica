#include "Sensor.h"

Sensor::Sensor(int trigPin, int echoPin)
{
     _ultraOne.begin(trigPin, echoPin);
	 _double = false;
}

Sensor::Sensor(int trigPin, int echoPin, int trigPin2, int echoPin2)
{
	_ultraOne.begin(trigPin, echoPin);
	_ultraTwo.begin(trigPin2, echoPin2);
	_double = true;
}

bool Sensor::isCloser(int x)
{
	if (!_double)
		return _ultraOne.isCloser(x);
	
	else
	{
		if (_ultraOne.isCloser(x) && _ultraTwo.isCloser(x))
			return true;
		else
			return false;
	}
}

bool Sensor::isFarDual()
{
	if (_ultraOne.getCentimeter() > _ultraTwo.getCentimeter())
		return true;
	return false;
}



