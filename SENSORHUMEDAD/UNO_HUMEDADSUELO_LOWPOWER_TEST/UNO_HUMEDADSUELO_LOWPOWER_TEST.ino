/*
  LECTURA DEL SENSOR DE HUMEDAD EN EL SUELO CADA 0,5 SEG
  APTO PARA MOSTRAR POR LA CONSOLA GRAFICA
  
  LOW POWER
  https://github.com/rocketscream/Low-Power
  
  Maneja alimentación del sensor desde un puerto para reducir consumo
*/

#include "LowPower.h"

#define CANTIDAD 4

#define ALIM_SENSOR 4 //pin 4

int sensorHumedadSuelo = 0;

int veces = 0;

void setup() {

  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(ALIM_SENSOR, OUTPUT);
  digitalWrite(ALIM_SENSOR, LOW);
}

void loop() {

  // ATmega328P, ATmega168
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                SPI_OFF, USART0_ON, TWI_OFF);
  delay(10);
  
  veces++;

  if (veces == CANTIDAD)
  {
    veces = 0;

    //Alimenta sensor
    digitalWrite(ALIM_SENSOR, HIGH);
    delay(250);
    // promedia lecturas
    sensorHumedadSuelo = analogRead(A0);
    sensorHumedadSuelo += analogRead(A0);
    sensorHumedadSuelo += analogRead(A0);
    sensorHumedadSuelo += analogRead(A0);

    //Apaga Sensor
    digitalWrite(ALIM_SENSOR, LOW);

    // map a un rango de salida
    //int sensorEscalado = map(sensorHumedadSuelo, 0, 1023, 0, 100);
    Serial.println(sensorHumedadSuelo / 4);
  }
}
