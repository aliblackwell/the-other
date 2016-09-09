/*

  This is the main file for the interactive light project. It will be uploaded to each Arduino.

  The code that animates the lights is saved in a separate file called lights.h

  The code that reads from the sensor is saved in a separate file called sensors.h

*/

// Load libraries for MPU6050
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"


int lightZapper = 9; // store pin 9 as our light controller

int arduinoNumber = 1; // which arduino are we working with?

// 2 – 6 should be THROWTATE
#define THROWTATE

// 1 should be NOTHROW
//#define NOTHROW
boolean stoppedThrow = false;

// 3, 4, 5 should be CENTRIFUGAL
//#define CENTRIFUGAL

// Crete an instance of MPU6050 called mpu
MPU6050 mpu;

#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards

int led_pin = 13;
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

int myPitch = 0; // variable needed to horizontal to verrtical function
float lightStrength = 0; // variable needed to horizontal to verrtical function

void setup() {

  Wire.begin();


  // test the connection to the I2C bus, sometimes it doesn't connect
  // keep trying to connect to I2C bus if we get an error
  boolean error = true;
  while (error) {
     Wire.beginTransmission(104);
     error = Wire.endTransmission(); // if error = 0, we are properly connected
     if (error) { // if we aren't properly connected, try connecting again and loop
       Serial.println("  ");
       Serial.println("Not properly connected to I2C, trying again");
       Serial.println(" ");
       Wire.begin();
       TWBR = 24; // 400kHz I2C clock
     }
  }
  Serial.println("Properly connected to I2C");

  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  Serial.begin(115200);
  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  Serial.print(arduinoNumber);
  mpu.initialize();

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
  delay(2);

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  Serial.print(devStatus);
  devStatus = mpu.dmpInitialize();
  Serial.print(devStatus);
  // supply your own gyro offsets here, scaled for min sensitivity

  setGyroOffsets(arduinoNumber);

  if (devStatus == 0)
  {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  else
  {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }

  // Setup our pin to control the voltage into the LEDs
  pinMode(lightZapper, OUTPUT);

}


void loop() {
  // if programming failed, don't try to do anything
  if (!dmpReady) return;
  while (!mpuInterrupt && fifoCount < packetSize) {}
  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024)
  {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  }
  else if (mpuIntStatus & 0x02)
  {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

    #ifdef THROWTATE

      int acceleration = totalAcceleration();

      if (acceleration >= 9000) {
        Serial.print("THROW");
        digitalWrite(lightZapper, LOW);
        delay(100);
        stoppedThrow = true;
      } else {
        //Serial.print("ROTATE");
        detectRotation(stoppedThrow);
        stoppedThrow = false;
      }

    #endif

    #ifdef NOTHROW

      detectRotation(stoppedThrow);

    #endif

    // For testing, configure options in gyro.ino to see the data
    // outputSensorValues();

    // blink LED to indicate activity
    // blinkState = !blinkState;
    // digitalWrite(led_pin, LOW);
  }
}
