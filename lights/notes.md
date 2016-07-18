#### Basic Sensor test

Does the sensor give readings back to the Serial monitor?

#### Advanced Sensor test

With the battery plugged in, does the transistor respond to the sensor for > 5m?

#### Light 1

Basic Sensor test: fail

Reason: SCL to A5 has no charge
A5 not giving any charge

Have resoldered the A5 to the bottom but it always stops showing a current when soldered to SCL. SCL chip also get extremely hot, much hotter than the others.

Conclusion: bust SCL on the sensor

#### Light 2: FAIL

Basic Sensor test: fail

Advanced Sensor test:

All soldered joints on sensor working.

Gets to DMP initialisation and freezes.

Have tried all sorts:

* script that doesn't use interrupts
* [clearing FIFO buffer](http://arduino.stackexchange.com/questions/10308/how-to-clear-fifo-buffer-on-mpu6050)
* [Waiting to connect properly](http://www.i2cdevlib.com/forums/topic/113-mpu6050-dmp-sketch-hangs-sometimes/#entry373) (does this fix the hanging issue?)

[uploading code failed numerous times with this error](http://forum.arduino.cc/index.php?topic=28223.0)

Conclusion: shorted sensor, probably by touching 12V to digital pin. Oops.

#### Light 3

Basic Sensor test: fail

Advanced Sensor test: fail

// Voltage out of transistor not being regulated.

SCL no charge
SDA no charge

Conclusion: bust MPU6050. Same as above.

#### Light 4: FAIL

Basic Sensor test: fail

Advanced Sensor test: fail

When tested with a multimeter, SCL and SDA are only registering a tiny bit of current, much less than Light 5.

Main.ino serial is blank. i2c-scanner just scans.

Conclusion: bust MPU6500 chip

#### Light 5

Basic Sensor test: pass

Advanced Sensor test: pass

This board ran Throwtate mode successfully for 45 minutes sitting in place in its bulb. [Here is a video of it in action](https://goo.gl/photos/sgEHjvnzzeM1a45N9). It has been sent to rehearsals.
