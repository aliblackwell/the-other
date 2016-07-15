/*
  acknowledgeSetup

  This function should give the user a signal that the Arduino
  has turned on successfully.
*/

void acknowledgeSetup() {
  digitalWrite(lightZapper,1);
  delay(500);
  digitalWrite(lightZapper,0);
  delay(500);
}

/*
  updateLightRotationAnimation

  This function should update the light when the user rotates the device
*/

void  updateLightRotationAnimation(int yawNumber) {

  analogWrite(lightZapper, yawNumber); // update the light

}