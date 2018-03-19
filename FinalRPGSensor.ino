
#include "Adafruit_TCS34725.h"

char  RBGInput[4][10]; //2d array that has only 1 raw for now
int columNumSensor1 = 0;
int columNumSensor2 = 0;
int columNumSensor3 = 0;
int columNumSensor4 = 0;

char determineInsturment;




#include "Wire.h"
extern "C" {
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

Adafruit_TCS34725 tcs = Adafruit_TCS34725 ( TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X ) ;


int onlyOnce = 1;
#define TCAADDR 0x70

//------------------------------------------------------------------------------------------------------------------
//check which RPG sensor
void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//if statments to add to the aray
void addToArray(int sensorNum, int columNum, float r, float g, float b) {
  if ( g >= 1.25) {
    RBGInput[sensorNum][columNum] = 'g';
    Serial. print ( " green found" );
  }
  else if (r >= 1.50) {
    RBGInput[sensorNum][columNum] = 'r';
    Serial. print ( " red found" );

  }
  else if (b >= 1.39) {
    RBGInput[sensorNum][columNum] = 'b';
    Serial. print ( " blue found" );
  }
  else {
    RBGInput[sensorNum][columNum] = 'n'; //n for nothing
    Serial. print ( " nothing Added" );

  }
}

//----------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//print the values for debuging purposes
void printValues(int num, uint16_t clearcol, float r, float g, float b) {
  Serial. print ( " \t Clear" + (String)num + ":") ; Serial. print ( clearcol ) ;
  Serial. print ( " \t Red:" + (String)num + ":" ) ; Serial. print ( r ) ;
  Serial. print ( " \t Green:" + (String)num + ":" ) ; Serial. print ( g ) ;
  Serial. print ( " \t Blue:" + (String)num + ":" ) ; Serial. print ( b) ;
}

//----------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//Determine which insturment to send data to
int retuenInsturmentNumber(uint16_t clearcol, float r, float g, float b) {
  // to be made once discussed
  return 0;
}


//----------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
// standard Arduino setup()
void setup()
{
  while (!Serial);
  delay(1000);

  Wire.begin();

  Serial.begin(9600);
  Serial.println("\nTCAScanner ready!");

  for (uint8_t t = 0; t < 8; t++) {
    tcaselect(t);
    Serial.print("TCA Port #"); Serial.println(t);

    for (uint8_t addr = 0; addr <= 127; addr++) {
      if (addr == TCAADDR) continue;

      uint8_t data;
      if (! twi_writeTo(addr, &data, 0, 1, 1)) {
        Serial.print("Found I2C 0x");  Serial.println(addr, HEX);
      }
    }
  }
  Serial.println("\ndone");


}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

//Standered arduino loop
void loop()
{

  while ( columNumSensor1 < 10 && columNumSensor2 < 10 && columNumSensor3 < 10 && columNumSensor4 < 10) {
    Serial.println("");
    tcaselect(2);
    uint16_t clearcol2, red2, green2, blue2 ;
    float average2, r2, g2, b2 ;
    delay ( 100 ) ;  // color measurement takes c. 50ms
    tcs. getRawData ( &red2, & green2, & blue2, & clearcol2 ) ;

    // average of RGB for the first one
    average2 =  ( red2 + green2 + blue2 ) / 3 ;
    r2 = red2 / average2 ;
    g2 = green2 / average2 ;
    b2 = blue2 / average2 ;

    //to view the real time value of red, green and blue
    printValues(2, clearcol2, r2, g2, b2);
    determineInsturment =  retuenInsturmentNumber(clearcol2, r2, g2, b2);

    boolean black2 = (clearcol2 >= 382 && r2 >= 0.96 && g2 >= 1.10 && b2 >= 0.96 );
    boolean white2 = ( clearcol2 >= 3500);

    if ( white2) {
      delay(1000);

      //-------------------------------------------------------------------------------------------------------------------------------------
      Adafruit_TCS34725 tcs3 = Adafruit_TCS34725 ( TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X ) ;
      tcaselect(3);  // second rbg sensor
      uint16_t clearcol3, red3, green3, blue3 ;
      float average3, r3, g3, b3 ;
      delay ( 100 ) ;  // color measurement takes c. 50ms
      tcs3. getRawData ( & red3, & green3, & blue3, & clearcol3 ) ;
      // average of RGB sensor 2
      average3 =  ( red3 + green3 + blue3 ) / 3 ;
      r3 = red3 / average3 ;
      g3 = green3 / average3 ;
      b3 = blue3 / average3 ;

      //to view the real time value of red, green and blue
      printValues(3, clearcol3, r3, g3, b3);

      //add to array
      addToArray(0, columNumSensor1, r3, g3, b3);
      columNumSensor1++;

      //-----------------------------------------------------------------------------------------------------------------------------------
      Adafruit_TCS34725 tcs4 = Adafruit_TCS34725 ( TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X ) ;
      tcaselect(4);  // second rbg sensor
      uint16_t clearcol4, red4, green4, blue4 ;
      float average4, r4, g4, b4 ;
      delay ( 100 ) ;  // color measurement takes c. 50ms
      tcs4. getRawData ( & red4, & green4, & blue4, & clearcol4) ;
      // average of RGB sensor 2
      average4 =  ( red4 + green4 + blue4 ) / 3 ;
      r4 = red4 / average4 ;
      g4 = green4 / average4 ;
      b4 = blue4 / average4 ;

      //to view the real time value of red, green and blue
      printValues(4, clearcol4, r4, g4, b4);

      //add to array
      addToArray(1, columNumSensor2, r4, g4, b4);
      columNumSensor2++;

      //-----------------------------------------------------------------------------------------------------------------------------------
      Adafruit_TCS34725 tcs5 = Adafruit_TCS34725 ( TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X ) ;
      tcaselect(5);  // second rbg sensor
      uint16_t clearcol5, red5, green5, blue5 ;
      float average5, r5, g5, b5 ;
      delay ( 100 ) ;  // color measurement takes c. 50ms
      tcs5. getRawData ( & red5, & green5, & blue5, & clearcol5) ;
      // average of RGB sensor 2
      average5 =  ( red5 + green5 + blue5 ) / 3 ;
      r5 = red5 / average5 ;
      g5 = green5 / average5 ;
      b5 = blue5 / average5 ;

      //to view the real time value of red, green and blue
      printValues(5, clearcol5, r5, g5, b5);

      //add to array
      addToArray(2, columNumSensor3, r5, g5, b5);
      columNumSensor3++;

      //-----------------------------------------------------------------------------------------------------------------------------------
      Adafruit_TCS34725 tcs6 = Adafruit_TCS34725 ( TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X ) ;
      tcaselect(6);  // second rbg sensor
      uint16_t clearcol6, red6, green6, blue6 ;
      float average6, r6, g6, b6 ;
      delay ( 100 ) ;  // color measurement takes c. 50ms
      tcs6. getRawData ( & red6, & green6, & blue6, & clearcol6) ;
      // average of RGB sensor 2
      average6 =  ( red6 + green6 + blue6 ) / 3 ;
      r6 = red6 / average6 ;
      g6 = green6 / average6 ;
      b6 = blue6 / average6 ;

      //to view the real time value of red, green and blue
      printValues(6, clearcol6, r6, g6, b6);

      //add to array
      addToArray(3, columNumSensor4, r6, g6, b6);
      columNumSensor4++;

      //--------------------------------------------------------------------------------------------------------------------------------
      //keep looping until a black is seen in the first sensor to prevent over populating the array
      while (white2) {
        // boolean black2 = (clearcol2 >= 200 && r2 >= 1.04 && g2 >= 1.04 && b2 > 0.89 );
        // boolean white2 = (clearcol2 >= 850 && r2 >= 0.95 && g2 >= 1.09 && b2 >= 0.90);
        tcaselect(2);
        uint16_t clearcol2, red2, green2, blue2 ;
        float average2, r2, g2, b2 ;
        delay ( 100 ) ;  // color measurement takes c. 50ms
        tcs. getRawData ( &red2, & green2, & blue2, & clearcol2 ) ;

        // average of RGB for the first one
        average2 =  ( red2 + green2 + blue2 ) / 3 ;
        r2 = red2 / average2 ;
        g2 = green2 / average2 ;
        b2 = blue2 / average2 ;

        //to view the real time value of red, green and blue
        Serial.println(" Still White");
        printValues(2, clearcol2, r2, g2, b2);
        black2 = (clearcol2 >= 382 && r2 >= 0.96 && g2 >= 1.10 && b2 >= 0.96 );
        white2 = ( clearcol2 >= 1000 );

        if (black2 &&  !white2) {
          delay(1500);
          break;
        }

      }
    }
  }

  //print the array to test

  int newLine  = 0;
  if ( onlyOnce == 1) {
    Serial.println("");
    Serial.println("");
    for (int i = 0; i < 10; i++) {

      for (int j = 0; j < 4; j++) {
        if (newLine < 4) {
          Serial.print((String)RBGInput[j][i] + " ");
          newLine++;
          if(newLine == 4){
            newLine = 0;
            Serial.println("");
            break;
          }
        }
      }
    }
    onlyOnce++;
  }
}








