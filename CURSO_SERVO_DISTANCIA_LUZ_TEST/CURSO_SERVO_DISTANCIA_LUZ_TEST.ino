/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/
#include <Wire.h>
#include <BH1750FVI.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
BH1750FVI LightSensor;
Servo myservo;  // create servo object to control a servo

int val;    // variable to read the value

void setup() {
  Serial.begin(9600);
  Serial.println("INICIO");
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  LightSensor.begin();
  LightSensor.SetAddress(Device_Address_L); //Address 0x23
  LightSensor.SetMode(Continuous_H_resolution_Mode);

}

void loop() {
  if ( Serial.available()) {
    char ch = Serial.read();
    switch (ch) {
      //    case '0'...'9':
      //      //v = v * 10 + ch - '0';
      //      v = ch - '0';
      //      break;
      case 's':
        val = Serial.parseInt();
        myservo.write(val);
        break;
      case 'd':
        Serial.print("Ping: ");
        //Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
        Serial.print(sonar.convert_cm(sonar.ping_median()));
        Serial.println("cm");
        break;
      case 'l':
        uint16_t lux = LightSensor.GetLightIntensity();// Get Lux value
        Serial.print("Light: ");
        Serial.print(lux);
        Serial.println(" lux");
        break;
    }
  }
}

