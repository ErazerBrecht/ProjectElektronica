#include "Sensor.h"
#include "Robot.h"

Sensor uForward(9, 10);
Sensor uReverse(22, 24);
Sensor uRight(26, 28);
Sensor uLeft(30, 32);
Robot Wagen(5, 6, 4, 8, 11, 12);

// Wrapper class for MPU 6050 around Jeff Rowberg library
// 30/03/2015 by Brecht Carlier & Arne Schoonvliet
#include "Rotate.h"
Rotate rotate;


//float Angle;
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
			Wagen.Forward(150);
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
			Wagen.Reverse(150);
		}
		else
		{
			Wagen.Stop();
		}
	}

	else if (turnLeft)
	{
		Wagen.Left(150, -150);
		if (rotate.Degrees <= oldAngle - 82)
		{
			turnLeft = false;
		}
	}
	else{
		Wagen.Right(-150, 150);
		if (rotate.Degrees >= oldAngle + 82)
		{
			turnRight = false;
		}
	}
}
