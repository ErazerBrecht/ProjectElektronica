# ProjectElektronica
Arduino Robot

# What?
We will make an Arduino Robot.
Our robot can be controlled with a PS3 controller. 
We did this with a USB Host Shield and a Bluetooth dongle
- [Host Shield](http://img.dxcdn.com/productimages/sku_166217_2.jpg)
- [Bluetooth Donge](http://i00.i.aliimg.com/wsphoto/v0/574362168/USB-2-0-Mini-font-b-Bluetooth-b-font-font-b-V2-0-b-font-EDR.jpg)

This part of the robot is already done. We will also put this part on GitHub (ETA July 2015).

Now we are making our Robot autonomous! The robot should be able to move trough a maze.
We will use IR sensors for this! They are faster as there Ultrasonic counterparts. 
We needed them because the delay of the ultrasonic sensors caused bugs with the MPU (later more info)
We chose for the Sharp GP2Y0A41SK sensors.
The code of this part can be founded in this repo!
Feel free to use it!

We use the filtering library of J. Doggen
https://github.com/jeroendoggen/Arduino-signal-filtering-library
We use the median filter for smoother values!
At the moment this filter is disabled, it's causing bugs. We will look into this soon.

We also have a Gyroscope / Accelerometer. It's the MPU6050.
We use this to measure the rotationdegrees from our robot.
The main reason we have this, is to be sure we turn 90 degrees independant of the speed of our robot!
We made a wrapper library around the MPU 6050 library of Jeff Rowberg (https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050)

Feel free to use this if his library is to difficult for you. Our library gives back a bool when it's done with measuring. And than you can check the degrees with a simple variable, no need for quaternation and etc (this is all done for you!)

# 2 branches?
Yeah we have 2 seperate branches. One is the program used for solving the maze.
The other one (Level 3) is used to find an object in a maze.

To find this object we use IR phototransistors (BPX 43). This is the scheme we used:
http://users.skynet.be/fotoopa/fpga/bpw43.png for our recieving part. This is connected to the Arduino on the robot.
