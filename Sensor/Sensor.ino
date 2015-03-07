#include "Ultrasoon.h"
#include "Robot.h"

Ultrasoon uForward(9, 10);
Ultrasoon uReverse(22, 24);
Ultrasoon uRight(26, 28);
Ultrasoon uLeft(30, 32);
Robot Wagen(5, 6, 4, 8, 11, 12);

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

	if (!uForward.isCloser(10))
	{
		Wagen.Forward(150);
	}		
	else if (!uLeft.isCloser(10))
	{
		Wagen.Left(150, -150);
		delay(525);
	}
	else if (!uRight.isCloser(10))
	{
		Wagen.Right(-150, 150);
		delay(525);
	}
	else if (!uReverse.isCloser(10))
	{
		Wagen.Reverse(150);
	}
	else
	{
		Wagen.Stop();
	}
}