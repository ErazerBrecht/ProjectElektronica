#include "Sensor.h"
#include "Robot.h"
#include "Tone.h"

// Sensor classes. Class for measuring distance to wall!
Sensor uForward(3);
//Sensor uReverse(22, 24);
Sensor uSide(9, 8);
//Sensor uLeft(30, 32);

// Robot class. Class for driving the motors!
Robot Wagen(5, 6, 4, 8, 11, 12);

#define Speed 255
#define TurnAngle 85
#define MinDistance 5

// Wrapper class for MPU 6050 around Jeff Rowberg library
// 30/03/2015 by Brecht Carlier & Arne Schoonvliet
#include "Rotate.h"
Rotate rotate;

enum Direction {
	Left,
	Right
};

Direction direction;
bool turn;
int angle;

int compensate;

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

	//Determine which side the robot needs to ue for compensating!
	DetermineCompensationSide();
}

void loop() {
	rotate.Measure();
	if (rotate.Ready)
		Drive();
}

//Drive part!
void Drive()
{
	//Serial.println(rotate.Degrees);

	if (!turn)
	{
		/*
		Serial.print("Forward Closer");
		Serial.println(uForward.isCloser(MinDistance));
		Serial.print("Both Closer: ");
		Serial.println(uSide.bothCloser(MinDistance));
		*/

		if (!uForward.isCloser(MinDistance))
		{
			//If there is more space than 30 cm there is a hole. No need to compensate!
			if (uSide.isCloser(compensate, 30))
			{
				int SpeedLeft;
				int SpeedRight;

				if (uSide.isCloser(compensate, 8))			//[0] is right sensor!
				{
					SpeedRight = Speed;
					SpeedLeft = Speed - 45;			
				}
				else if (!uSide.isCloser(compensate, 12))	//[0] is right sensor!
				{
					SpeedRight = Speed - 25;
					SpeedLeft = Speed;
				}
				else if (!uSide.isCloser(compensate, 13))	//[0] is right sensor!
				{
					SpeedRight = Speed - 45;
					SpeedLeft = Speed;			
				}
				else
					SpeedRight = SpeedLeft = Speed;

				if (compensate == 0)
					Wagen.Turn(SpeedRight, SpeedLeft);
				else
					Wagen.Turn(SpeedLeft, SpeedRight);
			}
			else
				Wagen.Forward(Speed);
		}

		else if (uSide.bothCloser(10))
		{
			//Serial.println("Ingesloten");
			//Wagen.Stop();
			turn = true;
			direction = Left;	//Rotate to left (or right doesn't matter) for 180 degrees
			angle = 179;
		}

		else
		{
			//If the return value is 0 then sensor 0 has te most place to turn. Sensor 0 is the right sensor!
			//Serial.println("Draaien!!");

			if (uSide.calculateTurnDirection() == 0)
			{
				direction = Right;
				//Serial.println("RIGHT");
			}
			else
			{
				direction = Left;
				//Serial.println("LEFT");
			}

			angle = TurnAngle;
			turn = true;			//Enable turn bool. This will activate the correct turn part of program.
		}
	}

	else
		Turn();
}

//This function is used to turn the robot!
void Turn()
{
	/*Serial.print("Meting: ");
	Serial.println(abs(rotate.Degrees));
	Serial.print("Gewenst: ");
	Serial.println(angle);
	*/
	if (abs(rotate.Degrees) >= angle)
	{
		turn = false;
		Wagen.Stop();			//This is needed for better stability for MPU otherwise the robot drives while he's initializing...
		rotate.Reset();
		DetermineCompensationSide();
	}

	else
	{
		if (direction == Left)
			Wagen.Turn(135, -135);
		else
			Wagen.Turn(-135, 135);
	}
}

//This function will determine of the robot has to compensate to the right wall or left wall!
void DetermineCompensationSide()
{
	//compensate = uSide.closestSensor();
	compensate = 0;
}