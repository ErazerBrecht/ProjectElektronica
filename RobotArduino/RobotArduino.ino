#include "Sensor.h"
#include "Robot.h"

Sensor uForward(9, 10);
Sensor uReverse(22, 24);
Sensor uRight(26, 28);
Sensor uLeft(30, 32);
Robot Wagen(5, 6, 4, 8, 11, 12);

#define Speed 200
#define TurnAngle 83

// Wrapper class for MPU 6050 around Jeff Rowberg library
// 30/03/2015 by Brecht Carlier & Arne Schoonvliet
#include "Rotate.h"
Rotate rotate;

float oldAngle;
bool turnLeft;
bool turnRight;

//Interrupt Service Routine
void dmpDataReady() {
	rotate.mpuInterrupt = true;
}

void setup() {
	attachInterrupt(0, dmpDataReady, RISING);

	// initialize serial communication
	Serial.begin(115200);
	// begin our wrapper library (init mpu)
	rotate.begin();
}

void loop() {
	rotate.Measure();
	if (rotate.Ready)
		Drive();
}

//Drive part!
void Drive()
{
	if (!turnLeft && !turnRight)
	{
		if (!uForward.isCloser(15))
		{
			Wagen.Forward(Speed);
		}

		else if (!uLeft.isCloser(15))
		{
			//Reset degrees
			rotate.Reset();
			oldAngle = 0;

			//Enable turn bool. This will activate the correct turn part of program.
			turnLeft = true;
		}


		else if (!uRight.isCloser(15))
		{

			//Reset degrees
			rotate.Reset();
			oldAngle = 0;

			//Enable turn bool. This will activate to correct turn part of program.
			turnRight = true;
		}

		else if (!uReverse.isCloser(20))
		{
			Wagen.Reverse(Speed);
		}
		else
		{
			Wagen.Stop();
		}
	}

	else if (turnLeft)
	{
		Wagen.Left(Speed, -Speed);
		if (rotate.Degrees <= oldAngle - TurnAngle)
		{
			turnLeft = false;
		}
	}
	else{
		Wagen.Right(-Speed, Speed);
		if (rotate.Degrees >= oldAngle + TurnAngle)
		{
			turnRight = false;
		}
	}
}
