
// first 2d array for flag = 0
int numOfC0 = 5;
int numOfR0 = 4;
char RBGInput0[5][4];
char input0;
int currentR0 = 0;
int currentC0 = 0;
int check0 = 0;

//second 2d array for flag = 1
int numOfC1 = 5;
int numOfR1 = 4;
char RBGInput1[5][4];
char input1;
int currentR1 = 0;
int currentC1 = 0;
int check1 = 0;

//remaining veriables
char flag = "-1" ;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {

  //Serial.print("Start");
  if (Serial.available() > 0) {
    flag = Serial.read(); //

    // when flag = 0
    if (flag == '0') {
      Serial.print("flag0= " + (String)flag + "\n" );
      while ( check0 < (numOfC0 * numOfR0) ) { // loop throw until all the array is populated
        if (Serial.available() > 0) {
          input0 = Serial.read();
          if ( currentC0 < numOfC0   ) { // when the current value of collum is less than the total value of colum
            RBGInput0[currentC0][currentR0] = input0; // add to the specified position
            Serial.print("input " + (String)input0 + " added at position C= " + currentC0 + " R= " + currentR0   + " array value: " + (String)RBGInput0[currentC0][currentR0] + "\n");
            currentR0++; //incrument row by 1
            if (currentR0 == numOfR0) { // when current row is equal to total value of row then incremunt current collum by 1 and assign current row to 0
              currentC0++;
              currentR0 = 0;
            }
          }
          check0++;
        }

        //to print the 2d array to check if every thing was implemented correctly
        if ( currentC0 >= numOfC0) {
          for (int i = 0; i < numOfC0; i++) {
            for (int j = 0; j < numOfR0; j++) {
              Serial.print((String)RBGInput0[i][j] + "\n");
            }
            currentC0 = 0;
          }
        }
      }
    }
    //when  flag = 1
    //same as when flag = 0 but the vairables sames switched to 1
    else if ( flag == '1') {
      Serial.print("flag1= " + (String)flag + "\n" );
      while ( check1 < (numOfC1 * numOfR1) ) {
        if (Serial.available() > 0) {
          input1 = Serial.read();
          if ( currentC1 < numOfC1   ) {
            RBGInput1[currentC1][currentR1] = input1;
            Serial.print("input " + (String)input1 + " added at position C= " + currentC1 + " R= " + currentR1   + " array value: " + (String)RBGInput1[currentC1][currentR1] + "\n");
            currentR1++;
            if (currentR1 == numOfR1) {
              currentC1++;
              currentR1 = 0;
            }
          }
          check1++;
        }

        if ( currentC1 >= numOfC1) {
          for (int i = 0; i < numOfC1; i++) {
            for (int j = 0; j < numOfR1; j++) {
              Serial.print((String)RBGInput1[i][j] + "\n");
            }
            currentC1 = 0;
          }
        }
      }

    }
  }
}
