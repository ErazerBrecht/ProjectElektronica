#include "Ultrasoon.h"
#include "Robot.h"

Ultrasoon uForward(9, 10);
Ultrasoon uReverse(22, 24);
Ultrasoon uRight(26, 28);
Ultrasoon uLeft(30, 32);
Robot Wagen(5, 6, 4, 8, 11, 12);


enum Tristate {
	Reset,
	Forward,
	Reverse,
	Left,
	Right,
	Stop
};

Tristate b = Forward;
bool b2;
bool b3;

void setup() {
	Serial.begin(9600);
}

void loop() {
	/*
	Serial.print("Forward");
	Serial.println(uForward.getCentimeter());
	Serial.print("Reverse");
	Serial.println(uReverse.getCentimeter());
	*/

	b2 = false;
	b3 = false;
	b = Reset;

	if (uForward.isCloser(15) && uReverse.isCloser(15))
		b = Stop;
	else{
		if (uForward.isCloser(15))
			b = Forward;
		if (uReverse.isCloser(15))
			b = Reverse;
		if (uRight.isCloser(15))
			b2 = true;
		if (uLeft.isCloser(15))
			b3 = true;
	}

	
	if (b == Stop)
	{
		Wagen.Stop();
	}
	else  if (b == Forward)
	{
		if (b3 == false)
		{
			Wagen.Left(150, -150);
			delay(110);
		}
		else if (b2 == false)
		{
			Wagen.Right(-150, 150);
			delay(110);
		}
		else{
			Wagen.Reverse(150);
		}
	}
	else
	{
		Wagen.Forward(150);
	}

}