#include "Adafruit_TCS34725.h"

//SOA to pin A4
//SCL to pin A5

int numOfArray =0;
int FirstSensorC = 0;
char * RBGInput [10][1]; //2d array that has only 1 raw for now
 
 
// initialize Color Sensor object 
Adafruit_TCS34725 tcs = Adafruit_TCS34725 ( TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X ) ;
 
// setup () will be executed once when starting the Arduino 
void setup ( )  {
 
 // Serial communication to output the value in serial monitor 
 Serial. begin ( 9600 ) ; 
 
}
  
void loop ( )  {
 
 // the sensor returns values ​​for R, G, B and a Clear value 
 uint16_t clearcol, red, green, blue ; 
 float average, r, g, b ; 
 delay ( 100 ) ;  // color measurement takes c. 50ms 
 tcs. getRawData ( & red, & green, & blue, & clearcol ) ;
 

 
 // average of RGB 
 average =  ( red + green + blue ) / 3 ; 
 r = red / average ; 
 g = green / average ; 
 b = blue / average ;
 
// value of r, b, g depends on room and atmosphere. As of now the value for
// red is 1.55, the value for green is 1.15 and the value for blue is 1.15

//to view the real time value of red, green and blue
 Serial. print ( " \t Clear:" ) ; Serial. print ( clearcol ) ; 
 Serial. print ( " \t Red:" ) ; Serial. print ( r ) ; 
 Serial. print ( " \t Green:" ) ;Serial. print ( g ) ; 
 Serial. print ( " \t Blue:" ) ; Serial. print ( b ) ;

boolean black = (r >= 1.04 || g >= 1.04 || b > 0.89 );
boolean white = (clearcol >= 11500 );

 if( white && !black){

  if( g > 1.15){
  RBGInput[FirstSensorC][numOfArray] = 'g';
  FirstSensorC++;
   Serial. print ( " green found" );
   delay(200);
   
 }
 else if(r > 1.55) {
  RBGInput[FirstSensorC][numOfArray] = 'r';
  FirstSensorC++;
   Serial. print ( " red found" );
   delay(200);
   
 }
  else if(b > 1.15) {
  RBGInput[FirstSensorC][numOfArray] = 'b';
  FirstSensorC++;
   Serial. print ( " blue found" );
   delay(200);
   }
   else {
  RBGInput[FirstSensorC][numOfArray] = 'n'; //n for nothing
  FirstSensorC++;
   Serial. print ( " nothing Added" );
   delay(200);
   }
 delay(1000);
 }

 // output line 
 Serial. println ( "" ) ;
 
 // adjust wait time for serial debugging 
 delay ( 2000 ) ;
}



// get the values of array to be used by other team members 
  void returnArray( char [1][10]){
  char currentArray[numOfColums][numOfArray];
  for(int i =0; i < numOfArray; i++){
    for(int j=0; j< numOfColums; j++){
       currentArray[j][i] = RBGInput[j][i];
    }
  } 
      return currentArray;
  }















