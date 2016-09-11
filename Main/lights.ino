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

int currentBrightness;

void writeToLight(int brightness) {
  if (brightness != currentBrightness) {
    analogWrite(9, brightness);
    currentBrightness = brightness;
  }
}


