#include "Ultrasoon.h"
#include "Robot.h"

Ultrasoon uForward(9, 10);
Ultrasoon uReverse(22, 24);
Ultrasoon uRight(26, 28);
Robot Wagen(5, 6, 4, 8, 11, 12);


enum Tristate {
	Forward,
	Reverse,
	Left,
	Right,
	Stop
};

Tristate b = Forward;

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

	if (uForward.isCloser(10) && uReverse.isCloser(10))
		b = Stop;
	else{
		if (uForward.isCloser(10))
			b = Forward;
		if (uReverse.isCloser(10))
			b = Reverse;
	}

	
	if (b == Stop)
	{
		Wagen.Stop();
	}
	else  if (b == Forward)
	{

		Wagen.Reverse(150);
	}
	else
		Wagen.Forward(150);

}