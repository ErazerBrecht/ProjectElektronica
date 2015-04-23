#include "Sensor.h"
#include "Robot.h"

// Sensor classes. Class for measuring distance to wall!
Sensor uForward(9, 10);
Sensor uReverse(22, 24);
Sensor uRight(26, 28);
Sensor uLeft(30, 32);

// Robot class. Class for driving the motors!
Robot Wagen(5, 6, 4, 8, 11, 12);

#define Speed 200
#define TurnAngle 87
#define MinDistance 10

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
bool  variableturn;
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
	variableturn = false;
	if (!turn)
	{
		if (!uForward.isCloser(MinDistance))
		{
			Wagen.Forward(Speed);
			if (uLeft.isCloser(8))
			{
				variableturn = true;
				direction = VariableRight;

			}
			else if (uRight.isCloser(8))
			{
				variableturn = true;
				direction = VariableLeft;
			}
		}

		else if (!uLeft.isCloser(MinDistance))
		{
			//Reset degrees
			//rotate.Reset();
			angle = TurnAngle - rotate.Degrees;
			//Enable turn bool. This will activate the correct turn part of program.
			turn = true;
			direction = Left;
		}

		else if (!uRight.isCloser(MinDistance))
		{
			//Reset degrees
			//rotate.Reset();
			angle = TurnAngle - rotate.Degrees;
			//Enable turn bool. This will activate to correct turn part of program.
			turn = true;
			direction = Right;
		}

		/*else if (!uReverse.isCloser(MinDistance))
		{
			rotate.Reset();
			turn = true;
			direction = Around;
			angle = 184;
			Wagen.Reverse(Speed);
		}*/
		else
		{
			Wagen.Stop();
		}
	}
	if (turn || variableturn)
	{
		Turn();
	}
}

void Turn()
{

	if (direction == VariableLeft)
	{
		Wagen.Left(Speed, Speed - 35);
		Serial.println("COMPENSATE");
	}
	else if (direction == VariableRight)
	{
		Wagen.Right(Speed - 35, Speed);
		Serial.println("COMPENSATE");
	}
	else
	{
		if (direction == Left)
		{
			Wagen.Left(100, -100);
		}

		else
		{
			Wagen.Right(-100, 100);
		}

		/*Serial.print("meting: ");
		Serial.println(abs(rotate.Degrees));
		Serial.print("gewenst: ");
		Serial.println(angle);*/

		if (abs(rotate.Degrees) >= angle)
		{
			turn = false;
			Wagen.Stop();
			rotate.Reset();
		}
	}
}
