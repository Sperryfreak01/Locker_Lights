#include "SPI.h"
#include "Adafruit_WS2801.h"

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels
int RandRed = 0;
int RandBlue = 0;
int RandGreen = 0;
int RandRed1 = 0;
int RandBlue1 = 0;
int RandGreen1 = 0;
int RedPoint = 0;
int BluePoint = 0;
int GreenPoint = 0;
int redDiff =0;
int BlueDiff =0;
int GreenDiff=0;

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

void setup() {
    
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
  randomSeed(analogRead(0));
  
    RandRed = random(255);
  RandBlue = random(255);
  RandGreen = random(255);
  
  RedPoint = RandRed;
  BluePoint = RandBlue;
  GreenPoint = GreenPoint;
   uint32_t RGB = Color(RandRed,RandBlue,RandGreen);

  colorWipe (RGB, 0);
  
  Serial.begin(9600);
  Serial.println("Begin");
}


void loop() {

  if( RedPoint == RandRed1 ){
    if (  BluePoint == RandBlue1 ){
      if (  GreenPoint == RandGreen1 ){

     
  

    
 // RandRed1 = random(255);  
 // redDiff = abs( RandRed1 - RedPoint);
  int RedRange = (RedPoint * .33);
  do {
      RandRed1 = random(255);
      redDiff = abs( RandRed1 - RedPoint);
  } while (redDiff < RedRange);
 
 
  //RandBlue1 = random(255);
  //BlueDiff = abs( RandBlue1 - BluePoint);
  int BlueRange = (BluePoint * .33);
  do {
      RandBlue1 = random(255);
      BlueDiff = abs( RandBlue1 - BluePoint);
  }while (BlueDiff < BlueRange);
 
  
  //RandGreen1 = random(255);
  //GreenDiff = abs( RandGreen1 - GreenPoint);
  int GreenRange = (GreenPoint * .33);
  do {
      RandGreen1 = random(255);
      GreenDiff = abs( RandGreen1 - GreenPoint);
      }while (GreenDiff < GreenRange);
  
  
  Serial.println("randRed");
  Serial.print(RandRed1,DEC); 
  Serial.println("randBlue");
  Serial.print(RandBlue1,DEC);
  Serial.println("randGreen");
  Serial.print(RandGreen1,DEC);
  
  
      }
    }
  }
  

  if (RedPoint != RandRed1){
    if ( RedPoint < RandRed1){
      RedPoint ++;
    }
    if (RedPoint > RandRed1){
      RedPoint --;
      }
  }
  
  if (BluePoint != RandBlue1){
    if ( BluePoint < RandBlue1){
      BluePoint ++;
    }
    if (BluePoint > RandBlue1){
      BluePoint --;
    }
  }
  
  if (GreenPoint != RandGreen1){
    if ( GreenPoint < RandGreen1){
       GreenPoint ++;
    }
    if (GreenPoint > RandGreen1){
       GreenPoint --;
      }
  }
  
  Serial.println("RedPoint");
  Serial.print(RedPoint,DEC);
       
  Serial.println("BluePoint");
  Serial.print(BluePoint,DEC);
       
  Serial.println("GreenPoint");
  Serial.print(GreenPoint,DEC);
  int coeff = (pow((double)RedPoint / 255, 2.5) * 255 + 0.5);
  int rval = abs(coeff);
  coeff = (pow((double)BluePoint / 255,   2.5) * 255 + 0.5);
  int bval = abs(coeff);
  coeff = (pow((double)GreenPoint / 255, 2.5) * 255 + 0.5);
  int gval = abs(coeff);
  uint32_t RGB1 = Color(rval,bval,gval);
  
 colorWipe (RGB1, 50);
}


// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      
  }
  strip.show();
      delay(wait);
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}




