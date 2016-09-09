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

#### Sensor: MPU6050

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

### Rough notes

* Load goes into collector
* Negative LEDs go into collector
* Emitter goes into Ground
* Base has a 1k fuse between pin 9 and base

3528-5M / 120LED 12V Lights

9V Batteries in series

[Our LEDs](https://www.amazon.co.uk/gp/product/B00XKSNH7C/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1)

* LED Type: 3528 SMD
* LED Quantity: 600 leds/roll, 5m/roll
* Power Consumption: 32-40w/roll
* Protection Grade: IP65 (Waterproof)
* Emitting Color: Cool white (6000k-7500k)
* Viewing Angle: 120°
* Operating Voltage: DC 12V
* Power Adapter for 5M: 5A(60W)
* Size (+/- 1mm): L: 500cm * W: 0.8cm
* Storage Temperature: -20° to +50°
* Life Span: 50,000 Hours



Notes:

* [Transistor vs Mosfet](http://sensitiveresearch.com/elec/DoNotTIP/index.html)
* [Cutting and working with LED strips](https://www.led-supplies.com/led-strips/cut-connect-power-led-strip/)
* [Powering LEDs using transistor (video)](https://www.youtube.com/watch?v=bvvnRSeSdKI)


### [Powering LED strip](https://www.led-supplies.com/led-strips/cut-connect-power-led-strip/)

Powering
We’ll now look at powering LED strip. It’s important that you don’t run too much LED strip as a single linear length or the high current being drawn into the strip can cause damage. We suggest that for 4.8W per metre strip, a maximum run of 10 metres is powered, and for 9.6W per metre strip a maximum of  10 metres if powered. If you do need to power more than this, then the LED strip should be wired in parallel to the PSU to avoid any damage.

When selecting a power supply, we suggest allowing 20% headroom. By this, we mean if your LED strip requires 48W, 20% added to 48W is 57.6W so the next largest power supply would be our 60W power supply. Its OK to use a power supply that can provide more than is required. By you should never use a power supply that is rated the same as your strip requires or less.

To calculate how much power in Watts you need. Simply multiply the Watts per metre of the strip by the length of strip you are powering. So if you are powering 5 metres of 4.8 Watts per metre strip just multiply 5 metres by 4.8W per metre giving you 24 Watts. Then adding the 20% headroom onto 24 watts gives you 28.8 Watts, so a power supply rated at 30 Watts or 40 Watts would be perfect. Even a 60 Watt or 90W power supply is acceptable as your LED strip will only draw the power it needs from the PSU.

#### Our LEDs
12W per meter
10 meters = 120W

9V battery = 500mah

Watts = Amps x Volts

500mah * 9V =
Roughly speaking, a 500 mA-hour battery can put out 500 mA for 1 hour so 9 volts x .5 amps = 4.5 watts for 1 hour.
