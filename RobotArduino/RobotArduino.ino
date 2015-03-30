#include "Sensor.h"
#include "Robot.h"

Sensor uForward(9, 10);
Sensor uReverse(22, 24);
Sensor uRight(26, 28);
Sensor uLeft(30, 32);
Robot Wagen(5, 6, 4, 8, 11, 12);

// I2C device class (I2Cdev) Arduino sketch for MPU6050
// 6/21/2012 by Jeff Rowberg <jeff@rowberg.net>
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

MPU6050 mpu;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

float Angle;
float oldAngle;
bool turnLeft;
bool turnRight;

// ================================================================
// ===               INTERRUPT SERVICE ROUTINE                  ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
	mpuInterrupt = true;
}



// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
	// initialize serial communication
	Serial.begin(115200);

	// join I2C bus (I2Cdev library doesn't do this automatically)
	Wire.begin();
	TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
	mpu.initialize();
	Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
	devStatus = mpu.dmpInitialize();

	// supply your own gyro and acc offsets here, scaled for min sensitivity
	// use calibrate test for automatic calculation of offsets
	mpu.setXAccelOffset(-3795);
	mpu.setYAccelOffset(349);
	mpu.setZAccelOffset(2239);
	mpu.setXGyroOffset(53);
	mpu.setYGyroOffset(-45);
	mpu.setZGyroOffset(-26);


	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		mpu.setDMPEnabled(true);

		// enable Arduino interrupt detection
		attachInterrupt(0, dmpDataReady, RISING);
		mpuIntStatus = mpu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();
	}
	else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print(F("DMP Initialization failed (code "));
		Serial.print(devStatus);
		Serial.println(F(")"));
	}
}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
	// if programming failed, don't try to do anything
	if (!dmpReady) return;

	// wait for MPU interrupt or extra packet(s) available
	while (!mpuInterrupt && fifoCount < packetSize) {

	}

	// reset interrupt flag and get INT_STATUS byte
	mpuInterrupt = false;
	mpuIntStatus = mpu.getIntStatus();

	// get current FIFO count
	fifoCount = mpu.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
		//Serial.println(F("FIFO overflow!"));

		// otherwise, check for DMP data ready interrupt (this should happen frequently)
	}
	else if (mpuIntStatus & 0x02) {
		// wait for correct available data length, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

		// read a packet from FIFO
		mpu.getFIFOBytes(fifoBuffer, packetSize);

		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;

		// display Euler angles in degrees
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
		Angle = ypr[0] * 180 / M_PI;
		Serial.println(Angle, 0);

		//Drive part!
		if (!turnLeft && !turnRight)
		{
			if (!uForward.isCloser(15))
			{
				Wagen.Forward(150);
			}

			else if (!uLeft.isCloser(15))
			{
				//Reset degrees
				mpu.dmpInitialize();
				mpu.setDMPEnabled(true);
				oldAngle = 0;
				
				//Enable turn bool. This will activate the correct turn part of program.
				turnLeft = true;
			}

			
			else if (!uRight.isCloser(15))
			{
			
			//Reset degrees
			mpu.dmpInitialize();
			mpu.setDMPEnabled(true);
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
			if (Angle <= oldAngle - 82)
			{
				turnLeft = false;
			}
		}
		else{
			Wagen.Right(-150, 150);
			if (Angle >= oldAngle + 82)
			{
				turnRight = false;
			}
		}
	}
}
