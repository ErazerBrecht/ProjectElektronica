/*
  Rotate.cpp - Library for TB6612FNG
  Created by Brecht Carlier & Arne Schoonvliet, March 30, 2015.
  Released into the public domain.
*/

#include "Rotate.h"
#include "Arduino.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "helper_3dmath.h"


void Rotate::begin()
{
	
	// join I2C bus (I2Cdev library doesn't do this automatically)
	Wire.begin();
	TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
	
	// initialize device
    mpu.initialize();
	devStatus = mpu.dmpInitialize();

    // verify connection
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed")); 
	
	// load and configure the DMP
    devStatus = mpu.dmpInitialize();
	
	// reset gyro offsets here for calibration
	mpu.setXAccelOffset(-3553);
	mpu.setYAccelOffset(418);
	mpu.setZAccelOffset(2242);
	mpu.setXGyroOffset(39);
	mpu.setYGyroOffset(-56);
	mpu.setZGyroOffset(-40);

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        mpu.setDMPEnabled(true);

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

void Rotate::Measure()
{
	Ready = false;

    // if programming failed, don't try to do anything
    if (!dmpReady) 
      return;

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
			Degrees = ypr[0] * 180/M_PI;
			//Now the sketch knows measure is done.
			Ready = true;
    }	
}

void Rotate::Reset()
{
	begin();
	delay(100);
}
