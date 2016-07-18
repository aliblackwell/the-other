#### Basic Sensor test

Does the sensor give readings back to the Serial monitor?

#### Advanced Sensor test

With the battery plugged in, does the transistor respond to the sensor for > 5m?


#### Light 1

Basic Sensor test: fail

Reason: SCL to A5 has no charge
A5 not giving any charge

Have resoldered the A5 to the bottom but it always stops showing a current when soldered to SCL. SCL chip also get extremely hot, much hotter than the others.

Conclusion: bust SCL chip



#### Light 2: FAIL

Basic Sensor test: fail

Advanced Sensor test: 

All soldered joints on MPU working.

Gets to DMP initialisation and freezes.

Have tried all sorts:

* script that doesn't use interrupts 
* [clearing FIFO buffer](http://arduino.stackexchange.com/questions/10308/how-to-clear-fifo-buffer-on-mpu6050)
* [Waiting to connect properly](http://www.i2cdevlib.com/forums/topic/113-mpu6050-dmp-sketch-hangs-sometimes/#entry373) (does this fix the hanging issue?)


#### Light 3

Basic Sensor test: fail

Advanced Sensor test: fail

// Voltage out of transistor not being regulated.

SCL no charge
SDA no charge


#### Light 4: FAIL

Basic Sensor test: fail

Advanced Sensor test: 

Has an issue with the Gyro. Not drawing enough power. 


#### Light 5

Basic Sensor test: pass

Advanced Sensor test: fail

Works consistently (dare I say it) as in it regulates the current to the lights based on gyro data

Still has the universal issue of sensor readings drying up after a few minutes.
