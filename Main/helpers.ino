
/*
  printIntToSerial

  This function prints a single into to serial followed by a linebreak
*/

void printIntToSerial(int valueToPrint) {

  Serial.print(valueToPrint);
  Serial.print("\n");

}

/*
  removeNegativeSign

  To remove the negative numbers and make them positive
*/

int removeNegativeSign(int number) {
  if (number < 0) {
    number= -number;
  }
  return number;
}
