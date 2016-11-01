#include <BH1750FVI.h>
#include <Servo.h>

#define baja_veloc 200
#define alta_veloc 100
#define limite_luz 500

BH1750FVI LightSensor;
Servo Servo1 ;

int grado = 0;
boolean encontro = false ;
boolean grado20 = false ;

void setup() {
  // put your setup code here, to run once:
  LightSensor.begin();
  LightSensor.SetAddress(Device_Address_L); //Address 0x23
  LightSensor.SetMode(Continuous_H_resolution_Mode);
  Servo1.attach(9) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean girando = true  ;
  encontro = false ;
  //grado20 = false ;
  if (grado20 == true) {
    grado = grado + 20 ;
  }
  while (girando == true) {
    Servo1.write(grado);
    delay(baja_veloc);
    uint16_t luz = LightSensor.GetLightIntensity();// Get Lux value
    if (luz < limite_luz && encontro == true && grado20 == true) {
      girando = false ;
      break ;
    }
    if (grado == 180) {
      girando = false;
    }
    else if (luz < limite_luz) {
      if (encontro == false) {
        grado = grado + 5 ;
        grado20 = false ;
      }
      else {
        grado = grado + 10 ;
        grado20 = true ;
      }
    }
    else {
      encontro = true ;
      grado20 = false;
    }
  }
  girando = true ;
  encontro = false ;
  //grado20 = false ;
  if (grado20 == true) {
    grado = grado - 20 ;
  }
  while (girando == true) {
    Servo1.write(grado);
    delay(baja_veloc);
    uint16_t luz = LightSensor.GetLightIntensity();// Get Lux value
    if (luz < limite_luz && encontro == true && grado20 == true) {
      girando = false ;
      break ;
    }
    if (grado == 0) {
      girando = false;
    }
    else if (luz < limite_luz) {
      if (encontro == false) {
        grado = grado - 5 ;
        grado20 = false ;
      }
      else {
        grado = grado - 10 ;
        grado20 = true ;
      }

    }
    else {
      encontro = true ;
      grado20 = false;
    }
  }
}
