
void setGyroOffsets(int arduinoNumber) {

  int xAccelOffset, yAccelOffset, zAccellOffset;
  int xGyroOffset, yGyroOffset, zGyroOffset;

  switch (arduinoNumber) {
    case 1: xAccelOffset = -1841;
            yAccelOffset = 3080;
            zAccellOffset = 1617;
            xGyroOffset = 82;
            yGyroOffset = -11;
            zGyroOffset = 23;
            break;
            break;
    case 2: xAccelOffset = 326;
            yAccelOffset = 1913;
            zAccellOffset = 1593;
            xGyroOffset = 65;
            yGyroOffset = 23;
            zGyroOffset = 46;
            break;
    case 3: xAccelOffset = -1382;
            yAccelOffset = -834;
            zAccellOffset = 1499;
            xGyroOffset = 32;
            yGyroOffset = 22;
            zGyroOffset = 5;
            break;
    case 4: xAccelOffset = 2296;
            yAccelOffset = 2941;
            zAccellOffset = 1838;
            xGyroOffset = 96;
            yGyroOffset = -11;
            zGyroOffset = 12;
            break;
    default:xAccelOffset = 187; // default number 5
            yAccelOffset = 2323;
            zAccellOffset = 1380;
            xGyroOffset = 98;
            yGyroOffset = -56;
            zGyroOffset = 7;
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

  int yawNumber = ypr[0] * 180/M_PI; // get value of yaw number out of ypr array and convert to radians
  yawNumber=removeNegativeSign(yawNumber);
  yawNumber = map(yawNumber, 0, 180, 0, 255);
  printIntToSerial(yawNumber); // use a pretty print function from helpers.ino

  updateLightRotationAnimation(yawNumber); // use our updateLight function from lights.ino

}//

/*

  detectThrow

  This function should detect a throw

*/

boolean detectThrow() {
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetAccel(&aa, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);

//Create variables for absolute values of x, y and z motion//
  int x= removeNegativeSign(aaReal.x);
  int y= removeNegativeSign(aaReal.y);
  int z= removeNegativeSign(aaReal.z);
  //Adding the values of x, y, z together//
  int totalValue = (x + y + z);

  //if statement, if the total value is greater than 8000, we assume that the device is moving
  if(totalValue > 8000){
    // device is being thrown
    return true;
  }else{
    // device is not being thrown
    return false;
  }

}

/*

  detectThrow

  This function should detect a spin

*/

boolean detectSpin() {
  // Centrifugal force!
  return false;
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

  analogWrite(lightZapper, lightStrength); //set the led_pin value to the lightStrength value


}


/*

  detectCentrifugalForce

  This function should detect centrifugal force

*/

void detectCentrifugalForce() {


}




