#include "Adafruit_TCS34725.h"

//SOA to pin A4
//SCL to pin A5

int numOfArray =0;
int numOfColums = 1; // for now 
char * RBGInput [1][10]; //2d array that has only 1 colum for now
 
 
// initialize Color Sensor object 
Adafruit_TCS34725 tcs = Adafruit_TCS34725 ( TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X ) ;
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Libraries Needed For This Project
//------------------------------------------------------------------------------------
  #include <Wire.h>           // To Be Able To Use Sensors Like IMU9050
  #include <EEPROM.h>         // To Be Able To Store & Read Data Between Power Off
  #include <ESP8266WiFi.h>    // The Basic Function Of The ESP NOD MCU
//------------------------------------------------------------------------------------
// Defining I/O Pins
//------------------------------------------------------------------------------------
  #define       LED0      2         // WIFI Module LED
  #define       LED1      13        // Indicate Connectivity With Client #1
  #define       LED2      12        // Indicate Connectivity With Client #2
  #define       BUTTON    14        // Connectivity ReInitiate Button
//------------------------------------------------------------------------------------
// BUTTON Variables
//------------------------------------------------------------------------------------
  int           ButtonState;
  int           LastButtonState   = LOW;
  int           LastDebounceTime  = 0;
  int           DebounceDelay     = 50;
  const String  ButtonColor       = "BLUE";
//------------------------------------------------------------------------------------
// LED Delay Variables
//------------------------------------------------------------------------------------
  int           LEDState          = LOW;
  unsigned long CurrMillis        = 0;
  unsigned long PrevMillis        = 0;
  unsigned long Interval          = 1000;
//------------------------------------------------------------------------------------
// WIFI Authentication Variables
//------------------------------------------------------------------------------------
/* This Client Is Going To Connect To A WIFI Server Access Point
 * So You Have To Specify Server WIFI SSID & Password In The Code Not Here
 * Please See The Function Below Name (WiFi.Begin)
 * If WIFI dont need Any password Then WiFi.begin("SSIDNAME")
 * If WIFI needs a Password Then WiFi.begin("SSIDNAME", "PASSWORD")
 */
  char*         TKDssid;            // Wifi Name
  char*         TKDpassword;        // Wifi Password
//------------------------------------------------------------------------------------
// WIFI Module Role & Port
//------------------------------------------------------------------------------------
/* This WIFI Module Code Works As A Client
 * That Will Connect To A Server WIFI Modul With (IP ADDress 192.168.4.1)
 */
  int             TKDServerPort  = 9001;
  IPAddress       TKDServer(192,168,4,1);
  WiFiClient      TKDClient;
//====================================================================================

  void setup() 
  {
    // Setting The Serial Port ----------------------------------------------
    Serial.begin(115200);           // Computer Communication
    
    // Setting The Mode Of Pins ---------------------------------------------
    pinMode(LED0, OUTPUT);          // WIFI OnBoard LED Light
    pinMode(LED1, OUTPUT);          // Indicator For Client #1 Connectivity
    pinMode(LED2, OUTPUT);          // Indicator For Client #2 Connectivity
    pinMode(BUTTON, INPUT_PULLUP);  // Initiate Connectivity
    digitalWrite(LED0, !LOW);       // Turn WiFi LED Off
    
    // Print Message Of I/O Setting Progress --------------------------------
    Serial.println("\nI/O Pins Modes Set .... Done");

    // Starting To Connect --------------------------------------------------
    if(WiFi.status() == WL_CONNECTED)
    {
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      delay(50);
    }

    /* in this part it should load the ssid and password 
     * from eeprom they try to connect using them */
    
    WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
    WiFi.begin("TAKEONE", "");      // The SSID That We Want To Connect To

    // Printing Message For User That Connetion Is On Process ---------------
    Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");

    // WiFi Connectivity ----------------------------------------------------
    CheckWiFiConnectivity();        // Checking For Connection

    // Stop Blinking To Indicate Connected ----------------------------------
    digitalWrite(LED0, !HIGH);
    Serial.println("!-- Client Device Connected --!");

    // Printing IP Address --------------------------------------------------
    Serial.println("Connected To      : " + String(WiFi.SSID()));
    Serial.println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
    Serial.print  ("Server IP Address : ");
    Serial.println(TKDServer);
    Serial.print  ("Server Port Num   : ");
    Serial.println(TKDServerPort);
    // Printing MAC Address
    Serial.print  ("Device MC Address : ");
    Serial.println(String(WiFi.macAddress()));
    // Printing IP Address
    Serial.print  ("Device IP Address : ");
    Serial.println(WiFi.localIP());
    
    // Conecting The Device As A Client -------------------------------------
    TKDRequest();
  }

//====================================================================================
  
  void loop()
  {

    ReadButton();
   //-------------------------------------------------------------------------------

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
  RBGInput[numOfColums][numOfArray] = "g";
  numOfArray++;
   Serial. print ( " green found" );
   LEDState    = !digitalRead(LED1);
   digitalWrite(LED1, LEDState);
   TKDClient.println("Green Detected");
   TKDClient.flush();
   delay(200);
 }
 if(r > 1.55) {
  RBGInput[numOfColums][numOfArray] = "r";
  numOfArray++;
   Serial. print ( " red found" );
   LEDState    = !digitalRead(LED1);
   digitalWrite(LED1, LEDState);
   TKDClient.println("RED Detected");
   TKDClient.flush();
   delay(200);
 }
  if(b > 1.15) {
  RBGInput[numOfColums][numOfArray] = "b";
  numOfArray++;
   Serial. print ( " blue found" );
   LEDState    = !digitalRead(LED1);
   digitalWrite(LED1, LEDState);
   TKDClient.println("BLUE Detected");
   TKDClient.flush();
   delay(200);
 }

 // output line 
 Serial. println ( "" ) ;
 
 // adjust wait time for serial debugging 
 delay ( 100 ) ;
    
  
  }

//====================================================================================

  void ReadButton()
  {
    // Reading The Button
    int reading = digitalRead(BUTTON);

    // If It Doest Match The Previous State
    if(reading != LastButtonState)
    {
      LastDebounceTime = millis();
    }

    // To Iliminate Debounce
    if((millis() - LastDebounceTime) > DebounceDelay)
    {
      if(reading != ButtonState)
      {
        ButtonState = reading;
        
        if(ButtonState == LOW)
        {
          LEDState    = !digitalRead(LED1);
          digitalWrite(LED1, LEDState);
          Serial.println("<" + ButtonColor + "-SCORED>");
          TKDClient.println("<" + ButtonColor + "-SCORED>");
          TKDClient.flush();
        }
      }
    }

    // Last Button State Concidered
    LastButtonState = reading;
  }

//====================================================================================

  void CheckWiFiConnectivity()
  {
    while(WiFi.status() != WL_CONNECTED)
    {
      for(int i=0; i < 10; i++)
      {
        digitalWrite(LED0, !HIGH);
        delay(250);
        digitalWrite(LED0, !LOW);
        delay(250);
        Serial.print(".");
      }
      Serial.println("");
    }
  }

//====================================================================================

  void I2C_Begin()
  {
    /* ----------------------------------------------------------------------
     * Setting The I2C Pins SDA, SCL
     * Because We Didnt Specify Any Pins The Defult
     * SDA = D4 <GPIO2>, SCL = D5 <GPIO14> For ESP8266 Dev Kit Node MCU v3
     --------------------------------------------------------------------- */
    // Frequency Of The I2C
    #define TWI_FREQ  400000L       // I2C Frequency Setting To 400KHZ
    
    // If Ever You Needed To Use Wire I2C
    Wire.begin();                   // Begginning The I2C
    
    // Setting Up The I2C Of The MPU9250 ------------------------------------
    Wire.setClock(TWI_FREQ);        // Setting The Frequency MPU9250 Require
  }
        
//====================================================================================

  void TKDRequest()
  {
    // First Make Sure You Got Disconnected
    TKDClient.stop();

    // If Sucessfully Connected Send Connection Message
    if(TKDClient.connect(TKDServer, TKDServerPort))
    {
      Serial.println    ("<" + ButtonColor + "-CONNECTED>");
      TKDClient.println ("<" + ButtonColor + "-CONNECTED>");
    }
  }

//====================================================================================
