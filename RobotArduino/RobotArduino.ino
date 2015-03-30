#include "Sensor.h"
#include "Robot.h"

Sensor uForward(9, 10);
Sensor uReverse(22, 24);
Sensor uRight(26, 28);
Sensor uLeft(30, 32);
Robot Wagen(5, 6, 4, 8, 11, 12);

#define Speed 200
#define TurnAngle 84
#define MinDistance 15

// Wrapper class for MPU 6050 around Jeff Rowberg library
// 30/03/2015 by Brecht Carlier & Arne Schoonvliet
#include "Rotate.h"
Rotate rotate;

enum Direction {
	Left,
	Right,
	Around,
	VariableRight,
	VariableLeft
};

Direction direction;
bool turn;
int angle;

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
	if (!turn)
	{
		if (!uForward.isCloser(MinDistance))
		{
			Wagen.Forward(Speed);
			
			if (uLeft.isCloser(7))
			{
				turn = true;
				direction = VariableRight;
				if (rotate.Degrees > 0)
					angle = rotate.Degrees + 3;
				else
					angle = abs(rotate.Degrees) + 3;
				//rotate.Reset();
			}
			else if (uRight.isCloser(7))
			{
				turn = true;
				direction = VariableLeft;
				angle = abs(rotate.Degrees) + 3;
				//rotate.Reset();
			}
		}

		else if (!uLeft.isCloser(MinDistance))
		{
			//Reset degrees
			rotate.Reset();

			//Enable turn bool. This will activate the correct turn part of program.
			turn = true;
			direction = Left;
			angle = TurnAngle;
		}

		else if (!uRight.isCloser(MinDistance))
		{
			//Reset degrees
			rotate.Reset();

			//Enable turn bool. This will activate to correct turn part of program.
			turn = true;
			direction = Right;
			angle = TurnAngle;
		}

		else if (!uReverse.isCloser(MinDistance))
		{
			rotate.Reset();
			turn = true;
			direction = Around;
			angle = 184;
			//Wagen.Reverse(Speed);
		}
		else
		{
			Wagen.Stop();
		}
	}
	else
	{
		Turn();
	}
}

void Turn()
{
	if (direction == Left)
	{
		Wagen.Left(Speed, -Speed);
	}
	else if (direction == VariableLeft)
	{
		Wagen.Left(Speed, Speed - 15);
	}
	else if (direction == VariableRight)
	{
		Wagen.Right(Speed - 15, Speed);
		Serial.println("COMPENSATE");
	}
	else
	{
		Wagen.Right(-Speed, Speed);
	}
	if (abs(rotate.Degrees) >= angle)
	{
		turn = false;
	}
}
