/*
  acknowledgeSetup

  This function should give the user a signal that the Arduino
  has turned on successfully.
*/

void acknowledgeSetup() {

}

/*
  updateLightRotationAnimation

  This function should update the light when the user rotates the device
*/

void  updateLightRotationAnimation(int brightness) {

  analogWrite(lightZapper, brightness); // update the light

}


// void changeBrightnessOfLight(float euler) {
// 	analogWrite(lightZapper, euler);// we have set the brightness on the pinNumber:
// 	printFloatToSerial(euler[0]); 

// }

