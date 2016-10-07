/*
LECTURA DEL SENSOR DE HUMEDAD EN EL SUELO CADA 0,5 SEG
APTO PARA MOSTRAR POR LA CONSOLA GRAFICA
 */

int sensorHumedadSuelo = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorHumedadSuelo = analogRead(A0);
  // map a un rango de salida
  //int sensorEscalado = map(sensorHumedadSuelo, 0, 1023, 0, 100);
  Serial.println(sensorHumedadSuelo);

  delay(500);
}
