
void setGyroOffsets(int arduinoNumber) {

  int xAccelOffset, yAccelOffset, zAccellOffset;
  int xGyroOffset, yGyroOffset, zGyroOffset;

  switch (arduinoNumber) {
    case 1:
      xAccelOffset = -4490;
      yAccelOffset = 1394;
      zAccellOffset = 1141;
      xGyroOffset = 176;
      yGyroOffset = 66;
      zGyroOffset = 45;
      break;
    case 2:
      xAccelOffset = -858;
      yAccelOffset = -1190;
      zAccellOffset = 1791;
      xGyroOffset = 48;
      yGyroOffset = 54;
      zGyroOffset = -4;
      break;
    case 3:
      xAccelOffset = 65;
      yAccelOffset = 2791;
      zAccellOffset = 1481;
      xGyroOffset = 39;
      yGyroOffset = -13;
      zGyroOffset = 21;
      break;
    case 4:
      xAccelOffset = -2147;
      yAccelOffset = -1304;
      zAccellOffset = 1382;
      xGyroOffset = 194;
      yGyroOffset = 5;
      zGyroOffset = 4;
      break;
    case 5:
      xAccelOffset = -2580;
      yAccelOffset = 306;
      zAccellOffset = 1810;
      xGyroOffset = 61;
      yGyroOffset = 22;
      zGyroOffset = 7;
      break;
    default:
      xAccelOffset = 479; // default number 6
      yAccelOffset = -920;
      zAccellOffset = 1388;
      xGyroOffset = 54;
      yGyroOffset = -30;
      zGyroOffset = 17;
      break;
  }

  mpu.setXAccelOffset(xAccelOffset);
  mpu.setYAccelOffset(yAccelOffset);
  mpu.setZAccelOffset(zAccellOffset);
  mpu.setXGyroOffset(xGyroOffset);
  mpu.setYGyroOffset(yGyroOffset);
  mpu.setZGyroOffset(zGyroOffset);

}

void outputSensorValues() {

  // uncomment "OUTPUT_READABLE_QUATERNION" if you want to see the actual
  // quaternion components in a [w, x, y, z] format (not best for parsing
  // on a remote host such as Processing or something though)
  //#define OUTPUT_READABLE_QUATERNION

  // uncomment "OUTPUT_READABLE_EULER" if you want to see Euler angles
  // (in degrees) calculated from the quaternions coming from the FIFO.
  // Note that Euler angles suffer from gimbal lock (for more info, see
  // http://en.wikipedia.org/wiki/Gimbal_lock)
  //#define OUTPUT_READABLE_EULER

  // uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
  // pitch/roll angles (in degrees) calculated from the quaternions coming
  // from the FIFO. Note this also requires gravity vector calculations.
  // Also note that yaw/pitch/roll angles suffer from gimbal lock (for
  // more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
  // #define OUTPUT_READABLE_YAWPITCHROLL

  // uncomment "OUTPUT_READABLE_REALACCEL" if you want to see acceleration
  // components with gravity removed. This acceleration reference frame is
  // not compensated for orientation, so +X is always +X according to the
  // sensor, just without the effects of gravity. If you want acceleration
  // compensated for orientation, us OUTPUT_READABLE_WORLDACCEL instead.
  //#define OUTPUT_READABLE_REALACCEL

  // uncomment "OUTPUT_READABLE_WORLDACCEL" if you want to see acceleration
  // components with gravity removed and adjusted for the world frame of
  // reference (yaw is relative to initial orientation, since no magnetometer
  // is present in this case). Could be quite handy in some cases.
  //#define OUTPUT_READABLE_WORLDACCEL

  // uncomment "OUTPUT_TEAPOT" if you want output that matches the
  // format used for the InvenSense teapot demo
  //#define OUTPUT_TEAPOT

  #ifdef OUTPUT_READABLE_QUATERNION
      // display quaternion values in easy matrix form: w x y z
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      Serial.print("quat\t");
      Serial.print(q.w);
      Serial.print("\t");
      Serial.print(q.x);
      Serial.print("\t");
      Serial.print(q.y);
      Serial.print("\t");
      Serial.println(q.z);
  #endif

  #ifdef OUTPUT_READABLE_EULER
      // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetEuler(euler, &q);
      Serial.print("euler\t");
      Serial.print(euler[0] * 180/M_PI);
      Serial.print("\t");
      Serial.print(euler[1] * 180/M_PI);
      Serial.print("\t");
      Serial.println(euler[2] * 180/M_PI);
  #endif

  #ifdef OUTPUT_READABLE_YAWPITCHROLL
      // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      Serial.print("ypr\t");
      Serial.print(ypr[0] * 180/M_PI);
      Serial.print("\t");
      Serial.print(ypr[1] * 180/M_PI);
      Serial.print("\t");
      Serial.println(ypr[2] * 180/M_PI);
      Serial.println("\n");
      Serial.println(lightStrength);
  #endif

  #ifdef OUTPUT_READABLE_REALACCEL
      // display real acceleration, adjusted to remove gravity
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetAccel(&aa, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
      Serial.print("areal\t");
      Serial.print(aaReal.x);
      Serial.print("\t");
      Serial.print(aaReal.y);
      Serial.print("\t");
      Serial.println(aaReal.z);
  #endif

  #ifdef OUTPUT_READABLE_WORLDACCEL
      // display initial world-frame acceleration, adjusted to remove gravity
      // and rotated based on known orientation from quaternion
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetAccel(&aa, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
      mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
      Serial.print("aworld\t");
      Serial.print(aaWorld.x);
      Serial.print("\t");
      Serial.print(aaWorld.y);
      Serial.print("\t");
      Serial.println(aaWorld.z);
  #endif

}

/*

  detectRotation

  This function should detect rotation of the device and update the light

*/

void detectRotation() {

  //Need these methods to populate ypr
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetAccel(&aa, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

  // yawNumber is between -179 and 179
  int yawNumber = ypr[0] * 180/M_PI;


  yawNumber = removeNegativeSign(yawNumber);
  yawNumber = map(yawNumber, 0, 180, 5, 255);

  writeToLight(yawNumber);

  Serial.println(yawNumber);

}

void fadeFromValueToValue(int startBrightness, int targetBrightness, int speed) {
  while(startBrightness != targetBrightness) {
    writeToLight(startBrightness);
    if (startBrightness > targetBrightness) {
      startBrightness--;
    } else {
      startBrightness++;
    }
    delay(speed);
  }
}

/*

  totalAcceleration

  Calculates the total acceleration of the device

*/

int totalAcceleration() {
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetAccel(&aa, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);

//Create variables for absolute values of x, y and z motion//
  int x = removeNegativeSign(aaReal.x);
  int y = removeNegativeSign(aaReal.y);
  int z = removeNegativeSign(aaReal.z);
  //Adding the values of x, y, z together//
  int totalValue = (x + y + z);

  return(totalValue);

}

/*

  detectThrow

  This function should detect a throw

*/

boolean detectThrow() {

  int acceleration = totalAcceleration();

  //if statement, if the total value is greater than 8000, we assume that the device is moving
  if(acceleration > 8000){
    // device is being thrown
    return true;
  }else{
    // device is not being thrown
    return false;
  }

  // Serial.println(acceleration);

}

/*

  detectVerticalToHorizontal

  This function should detect a change in angle (vertical to horizontal)

*/

void detectVerticalToHorizontal() {

  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

  myPitch = removeNegativeSign(ypr[1]); //ypr is -180 to 180. This cahnges it to 0 to 360

  if (myPitch >= 0 && myPitch <= 90) { //if the  pitch is between 12 and 3 o clock
    lightStrength = (myPitch * 2.83333); //assign lightStrength a value which increases the fade
  }
  else if (myPitch >= 91 && myPitch <= 180) { //if the  pitch is between 3 and 6 o clock
    lightStrength = (myPitch - ((myPitch - 90)* 2)* 2.83333); //assign lightStrength a value which decreases the fade
  }
  else if (myPitch >= 181 && myPitch <= 270) { //if the  pitch is between 6 and 9 o clock
    lightStrength = ((myPitch - 180)* 2.83333); //assign lightStrength a value which increases the fade
  }
  else if (myPitch >= 271 && myPitch <= 360) { //if the  pitch is between 9 and 12 o clock
    lightStrength = (myPitch - ((myPitch - 270)* 2)* 2.83333); //assign lightStrength a value which decreases the fade
  }

  Serial.print(myPitch);
  Serial.print("\n");

  writeToLight(lightStrength); //set the led_pin value to the lightStrength value

}


/*

  detectCentrifugalForce

  This function should detect centrifugal force

*/

void detectCentrifugalForce() {


}
