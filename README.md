# ProjectElektronica
Arduino Robot

# What?
We will make an Arduino Robot.
Our robot can be controlled with a PS3 controller. 
We did this with a USB Host Shield and a Bluetooth dongle
- [Host Shield](http://img.dxcdn.com/productimages/sku_166217_2.jpg)
- [Bluetooth Donge](http://i00.i.aliimg.com/wsphoto/v0/574362168/USB-2-0-Mini-font-b-Bluetooth-b-font-font-b-V2-0-b-font-EDR.jpg)

Now we are making our Robot autonomous! The robot should be able to move trough a maze.
We will use ultrasoon sensors for this! They are cheaper as there IR counterparts. 
We chose for the HC-SR04.
The code of this part can be founded in this repo!
Feel free to use it!

We use the filtering library of J. Doggen
https://github.com/jeroendoggen/Arduino-signal-filtering-library
We use the median filter for smoother values!

We also have a Gyroscope / Accelerometer. It's the MPU6050.
Later more about this!
