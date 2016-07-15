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
//#define OUTPUT_READABLE_YAWPITCHROLL

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



void outputSensorValues() {

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

  // Need these methods to populate ypr
  //mpu.dmpGetQuaternion(&q, fifoBuffer);
  //mpu.dmpGetGravity(&gravity, &q);
  //mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

  //int yawNumber = ypr[0] * 180/M_PI; // get value of yaw number out of ypr array and convert to radians

  //printIntToSerial(yawNumber); // use a pretty print function from helpers.ino

  //updateLightRotationAnimation(yawNumber); // use our updateLight function from lights.ino

}//

/*

  detectThrow

  This function should detect a throw

*/

void detectThrow() {
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
         


//           To look at the indiviudal values of x, y, z//
//            Serial.print(aaReal.x);
//            Serial.print("  ");
//            Serial.print(aaReal.y);
//            Serial.print("  ");
//            Serial.print(aaReal.z);
//            Serial.print("\n");

//if statement, if the total value is greater than 8000, we assume that the device is moving//
           if(totalValue >8000){
            //if device is moving, the lights turn on//
            digitalWrite(lightZapper, HIGH);
            Serial.print("HIGH");
            Serial.print("\n");
            
           //if device is not moving, the lights turn off//
           }else{
            digitalWrite(lightZapper, LOW);
            Serial.print("LOW");
            Serial.print("\n");
            }
            

            }

/*

  detectVerticalToHorizontal

  This function should detect centrifugal force

*/

void detectVerticalToHorizontal() {


}


/*

  detectCentrifugalForce

  This function should detect centrifugal force

*/

void detectCentrifugalForce() {


}




