
/*
  This is a simple code to test BH1750FVI Light senosr
  communicate using I2C Protocol 
  this library enable 2 slave device address
  Main address  0x23 
  secondary address 0x5C 
  connect this sensor as following :
  VCC >>> 3.3V
  SDA >>> A4 
  SCL >>> A5
  addr >> A3
  Gnd >>>Gnd

  Written By : Mohannad Rawashdeh
  
 */
 
 // First define the library :

#include <Wire.h>
#include <BH1750FVI.h>
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN       4
#define NUMPIXELS 1


BH1750FVI LightSensor;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int rColor, gColor, bColor = 0;
unsigned long tiempo = 0;

void setup() {   // put your setup code here, to run once:
   Serial.begin(9600);
  LightSensor.begin();
    pixels.begin(); // This initializes the NeoPixel library.

  Serial.println("INICIO");
  /*
 Set the address for this sensor 
 you can use 2 different address
 Device_Address_H "0x5C"
 Device_Address_L "0x23"
 you must connect Addr pin to A3 .
 */
 // LightSensor.SetAddress(Device_Address_H);//Address 0x5C
 // To adjust the slave on other address , uncomment this line
  LightSensor.SetAddress(Device_Address_L); //Address 0x23
 //-----------------------------------------------
  /*
   set the Working Mode for this sensor 
   Select the following Mode:
    Continuous_H_resolution_Mode
    Continuous_H_resolution_Mode2
    Continuous_L_resolution_Mode
    OneTime_H_resolution_Mode
    OneTime_H_resolution_Mode2
    OneTime_L_resolution_Mode
    
    The data sheet recommanded To use Continuous_H_resolution_Mode
  */

  LightSensor.SetMode(Continuous_H_resolution_Mode);
  
  Serial.println("INICIO COLORIMETRO");
  tiempo=millis();
}



void loop() {
  // put your main code here, to run repeatedly:

  if(millis() - tiempo > 1000)
  {
    tiempo = millis();
  uint16_t lux = LightSensor.GetLightIntensity();// Get Lux value
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");

  }
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(0, pixels.Color(rColor, gColor, bColor));

  pixels.show(); // This sends the updated pixel color to the hardware.

  if ( Serial.available()) {

    char ch = Serial.read();
    switch (ch) {
      //    case '0'...'9':
      //      //v = v * 10 + ch - '0';
      //      v = ch - '0';
      //      break;
      case 'r':
        rColor = Serial.parseInt();
        break;
      case 'g':
        gColor = Serial.parseInt();
        break;
      case 'b':
        bColor = Serial.parseInt();
        break;
    }
  }
}
