# The Other

## Interactive Lighting

### The Circuit

#### Arduino

RED POWER -> ARD Vin # Power Arduino using battery pack

BATTERY GROUND -> ARD GND # Shared ground

#### Lights:

RED POWER -> LED RED # Lights, no resistor needed

LED BLACK -> TRANSISTOR COLLECTOR # Into the transistor

TRANSISTOR BASE -> ARD PIN 9 # Regulated voltage from Arduino

TRANSISTOR EMITTER -> ARD GND # Complete the circuit with shared ground

#### IMU:

[MPU6050 Overview](http://42bots.com/tutorials/arduino-uno-and-the-invensense-mpu-6050-6dof-imu/)

ARD 3.3V -> UCC # Power

ARD GND -> GND # Shared ground

ARD A4 -> SDA # [Just following orders](http://42bots.com/tutorials/arduino-uno-and-the-invensense-mpu-6050-6dof-imu/)

ARD A5 -> SCL # More following orders

INT -> ARD PIN 2 # Interrupt pin. [Useful reading on Arduino interrupts](http://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/)

#### Circuit to do:

Add a switch that is accessible from outside the casing between RED POWER and LED RED so the Light can be set in position and then turned on.

### The Four actions


#### Horizontal / Vertical:

Slow fade out going down
Slow fade in coming up

#### Turning on the axis:

Fade in and Out
Five second gap

#### Impact:

Light on, throw it light off, catch it light back on


#### Centrifugal Force:

Flashes faster and faster the faster it's spinning

