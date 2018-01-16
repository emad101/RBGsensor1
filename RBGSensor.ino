#include "Adafruit_TCS34725.h"

//SOA to pin A4
//SCL to pin A5
 
char RBGInput[10]; // putting the values of the rbg in an array to be used later. should be 2d array once we add more sesnors
int numOfArray =0; //current value of array
 
 
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

  if( g > 1.15){
  RBGInput[numOfArray] = 'g';
  numOfArray++;
   Serial. print ( " green found" );
   delay(200);
 }
 if(r > 1.55) {
  RBGInput[numOfArray] = 'r';
  numOfArray++;
   Serial. print ( " red found" );
   delay(200);
 }
  if(b > 1.15) {
  RBGInput[numOfArray] = 'b';
  numOfArray++;
   Serial. print ( " blue found" );
   delay(200);
 }

 // output line 
 Serial. println ( "" ) ;
 
 // adjust wait time for serial debugging 
 delay ( 100 ) ;
}


// get the values of array to be used by other team members 
  void returnArray( char []){
  char currentArray[numOfArray];
  for(int i =0; i < numOfArray; i++){
    currentArray[i] = RBGInput[i];
  }
  return currentArray;
}

