/*
  LECTURA DEL SENSOR DE HUMEDAD EN EL SUELO CADA 10 SEG
  APTO PARA MOSTRAR POR LA CONSOLA GRAFICA
  DATALOG SOBRE SD

    SD card attached to SPI bus as follows:
 ** MOSI - pin 11 on Arduino Uno
 ** MISO - pin 12 on Arduino Uno
 ** CLK - pin 13 on Arduino Uno
 ** CS - depends on your SD card shield or module.
     Pin 4 used here for consistency with other Arduino examples

*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

void setup() {

  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  Serial.println("Inicia SD");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("ERROR en SD o SD no presente. Programa detenido");
    // don't do anything more:
    digitalWrite(13, HIGH);
    return;
  }
  Serial.println("SD Iniciada");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {

    //guarda en el archivo el inicio de la captura
    dataFile.println("INICIA CAPTURA");

    dataFile.close();

  }
  // if the file isn't open, pop up an error:
  else {

    Serial.println("ERROR en datalog.txt");

  }

  delay(1000);
}

void loop() {

  // read the analog in value:
  String dataString = "";
  int sensorHumedadSuelo = analogRead(A0);
  // map a un rango de salida
  //int sensorEscalado = map(sensorHumedadSuelo, 0, 1023, 0, 100);
  dataString = String(sensorHumedadSuelo);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {

    dataFile.println(dataString);

    dataFile.close();

    // print to the serial port too:
    Serial.println(sensorHumedadSuelo);

  }
  // if the file isn't open, pop up an error:
  else {

    Serial.println("ERROR en datalog.txt");

  }

  delay(10000);
}
