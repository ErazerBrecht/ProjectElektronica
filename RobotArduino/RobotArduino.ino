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
			if (uSide.isCloser(0, 30))
			{
				if (uSide.isCloser(0, 8))				//[0] is right sensor!
					Wagen.Turn(Speed, Speed - 45);		//Compensate to left
				else if (!uSide.isCloser(0, 11))		//[0] is right sensor!
					Wagen.Turn(Speed - 25, Speed);		//Compensate to right
				else if (!uSide.isCloser(0, 12))		//[0] is right sensor!
					Wagen.Turn(Speed - 55, Speed);		//Compensate to right
				else
					Wagen.Forward(Speed);
			}
			else
				Wagen.Forward(Speed);
		}

		else if (uSide.bothCloser(MinDistance))
		{
			//Serial.println("STOP");
			Wagen.Stop();
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

		/*else if (!uReverse.isCloser(MinDistance))
		{
		rotate.Reset();
		turn = true;
		direction = Around;
		angle = 184;
		Wagen.Reverse(Speed);
		}*/
	}

	else
		Turn();
}

void Turn()
{
		if (direction == Left)
			Wagen.Turn(100, -100);
		else
			Wagen.Turn(-100, 100);

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
		}
	
}
