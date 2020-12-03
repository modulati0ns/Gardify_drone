// Liberias propias
#include <dhtLib.h>

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>


DHT dht(5, DHT11);                           // Instancia para el sensor de temperatura


float temperatura = 0;
float humedadaire = 0;

void dhtBegin(){
    dht.begin();
}


void lecturaSensor(){
    temperatura = dht.readTemperature();
    humedadaire = dht.readHumidity();
}


