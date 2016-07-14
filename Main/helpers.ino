
/*
  printIntToSerial

  This function prints a single into to serial followed by a linebreak
*/

void printIntToSerial(int valueToPrint) {
  Serial.print(valueToPrint);
  Serial.print("\n");
}