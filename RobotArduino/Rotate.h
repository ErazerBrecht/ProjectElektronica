/*
  Rotate.h - Wrapper Library for MPU 6050. We will use it for rotation measuring.
  Created by Brecht Carlier & Arne Schoonvliet, March 30, 2015.
  Released into the public domain. 
  GPL licensed
*/

#ifndef Rotate_h
#define Rotate_h

#include "Arduino.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "helper_3dmath.h"
#include "Wire.h"

class Rotate
{
  public:
    void begin();
	void Measure();
	void Reset();

	float Degrees;
	bool Ready;
	volatile byte mpuInterrupt;   // holds actual interrupt status byte from MPU
	
  private:
	//MPU Library
    MPU6050 mpu;
	
	int ax, ay, az,gx, gy, gz;
	
	//Variabeles & function for measuring
	// MPU control/status vars
	int mpuIntStatus;		// holds actual interrupt status byte from MPU
	bool dmpReady;			// set true if DMP init was successful
	byte devStatus;			// return status after each device operation (0 = success, !0 = error)
	int packetSize;			// expected DMP packet size (default is 42 bytes)
	int fifoCount;			// count of all bytes currently in FIFO
	byte fifoBuffer[64];	// FIFO storage buffer

	// orientation/motion vars
	Quaternion q;           // [w, x, y, z]         quaternion container
	VectorFloat gravity;    // [x, y, z]            gravity vector
	float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
	
};

#endif