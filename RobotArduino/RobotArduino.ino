#include "Sensor.h"
#include "Robot.h"
#include "Tone.h"

// Sensor classes. Class for measuring distance to wall!
Sensor uForward(5, 3);
//Sensor uReverse(22, 24);
Sensor uSide(9, 8);
//Sensor uLeft(30, 32);

// Robot class. Class for driving the motors!
Robot Wagen(5, 6, 4, 8, 11, 12);

//Tone class. For playing song
Tone t;
bool found;
bool NoScope = true;

#define Speed 100
#define TurnAngle 87
#define MinDistance 7

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

	//start the Tone library (playing song), add pin of speaker!
	t.begin(38);
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
	variableturn = false;
	
	if (NoScope && found == false)
	{
		Search();
	}
	else{
		if (!turn)
		{
			/*
			Serial.print("Forward Closer");
			Serial.println(uForward.isCloser(MinDistance));
			Serial.print("Both Closer: ");
			Serial.println(uSide.bothCloser(MinDistance));
			*/

			int IRRight = analogRead(A2);
			int IRLeft = analogRead(A1);

			if (IRRight < 100 || IRLeft < 100)
				found = true;

			if (!uForward.isCloser(MinDistance))
			{
				if (found)
				{
					if (IRRight < 100 || IRLeft < 100)
						Wagen.Forward(200);
					else if (IRRight < IRLeft)
						Wagen.Turn(-100, 100);
					else
						Wagen.Turn(100, -100);
				}
				else
				{
					//If there is more space than 20 cm there is a hole. No need to compensate!
					if (uSide.isCloser(0, 20))
					{
						if (uSide.isCloser(0, 8))			//[0] is right sensor!
						{
							variableturn = true;
							direction = VariableLeft;

						}
						else if (!uSide.isCloser(0, 9))		//[0] is right sensor!
						{
							variableturn = true;
							direction = VariableRight;
						}
					}
					else
						Wagen.Forward(Speed);
					

				}
			}

			else if (found)
			{
				if (IRLeft < 100 || IRRight < 100)
				{
					Wagen.Stop();
					t.playMario();
					found = false;
				}
				else{
					NoScope = true;
					found = false;
				}
			}

			else if (uSide.bothCloser(MinDistance))
			{
				//Serial.println("STOP");
				Wagen.Stop();
			}

			else{
				//If the return value is 0 then sensor 0 has te most place to turn. Sensor 0 is the righ sensor!
				//Serial.println("Draaien!!");
				//Serial.print("Random: ");
				//Serial.println(uSide.calculateTurnDirection());
				if (uSide.calculateTurnDirection() == 0)
				{
					///angle = TurnAngle - rotate.Degrees;
					angle = TurnAngle;
					//Enable turn bool. This will activate to correct turn part of program.
					turn = true;
					direction = Right;
					//Serial.println("RIGHT");
				}
				else{
					angle = TurnAngle;
					//angle = TurnAngle + rotate.Degrees;
					//Enable turn bool. This will activate the correct turn part of program.
					turn = true;
					direction = Left;
					//Serial.println("LEFT");
				}
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
		Wagen.Turn(Speed, Speed - 40);
	}
	else if (direction == VariableRight)
	{
		Wagen.Turn(Speed - 30, Speed);
	}
	else
	{
		if (direction == Left)
		{
			Wagen.Turn(100, -100);
		}

		else
		{
			Wagen.Turn(-100, 100);
		}

		
		/*Serial.print("Meting: ");
		Serial.println(abs(rotate.Degrees));
		Serial.print("Gewenst: ");
		Serial.println(angle);
		*/

		if (abs(rotate.Degrees) >= angle)
		{
			turn = false;
			Wagen.Stop();
			rotate.Reset();
			NoScope = true;
		}
	}
}

void Search()
{
	//Serial.println("LOL");

	if ((int)floor(rotate.Degrees) != -2)
	{
		//Serial.println(rotate.Degrees);
		int IRRight = analogRead(A2);
		int IRLeft = analogRead(A1);
		if (IRRight < 100 || IRLeft < 100)
		{
			found = true;
		}
		else{
			Wagen.Turn(-100, 100);
		}
	}
	else
	{
		NoScope = false;
		//Serial.println((int)floor(rotate.Degrees));
		//Serial.println("KLEIR");
	}
}
