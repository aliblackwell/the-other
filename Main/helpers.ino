
/*
  printIntToSerial

  This function prints a single into to serial followed by a linebreak
*/

void printIntToSerial(int valueToPrint) {

  Serial.print(valueToPrint);
  Serial.print("\n");

}

int removeNegativeSign(int number) { //To remove the negative numbers and make them positive//

  if (number < 0) { 
    number= -number;
    }
    return number;
  }




