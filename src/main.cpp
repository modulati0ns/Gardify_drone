// Liberias propias
#include <dhtLib.h>
#include <memoria.h>
#include <mqttConn.h>
#include <varGlobals.h>
#include <wifiConn.h>

// Liberias terceros
#include <Arduino.h>
#include <WiFi.h>

uint8_t droneAddress[6]; // QUITAR
bool configured = 0;
int id = abs(ESP.getEfuseMac());
String nombre = "";

void setup()
{
  Serial.begin(921600); // Comienzo del puerto Serial

  loadConfig();

  WiFi.begin(ssid, password);
  for (int i = 0; i < 7; i++)
  {
    Serial.print('.');
    delay(500);
  }
  
  

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Configured: ");
  Serial.println(configured);
  Serial.print("Nombre: "); // NO CONSIGO MOSTRAT EL NOMBRE A VER QUE PASA!!!
  Serial.println(nombre);
  Serial.print("ID: ");
  Serial.println(id);

  Serial.print("Estado del wifi: ");
  Serial.println(WiFi.status());
  if (configured == 0 || !(WiFi.status() == WL_CONNECTED))
  {
    // Se inicia el modo AP
    Serial.println("El dispositivo no está configurado");
    wifiServer();
    unsigned long previousTime = millis();
    while (configured == 0 || !(WiFi.status() == WL_CONNECTED))
    {
      if (millis() > previousTime + 300000)
      {
        Serial.println("Entrando en DeepSleep");
        // Entra cuando haya pasado el tiempo
        ESP.deepSleep(0);
      }
      else
      {
        Serial.println("El ESP esta en modo WifI");
        delay(2000);
      }
    }
    Serial.println("Dispositivo configurado con exito");
  }
  else
  {
    Serial.println("Dispositivo ya configurado con anterioridad");
    dhtBegin();          // Comienzo del sensor de temp y humedad
    WiFi.mode(WIFI_STA); // CAMBIAR AL TIPO DE WIFI NECESARIO PARA MQTT
  }
}

void loop()
{
  // Lectura de los datos DHT11
  lecturaSensor();

  delay(1000);

  Serial.println("Estamos en el loop");
  // if (sendData()){
  //   Serial.println("Los datos se enviaron correctamente");
  //   ESP.deepSleep(5e6);
  // }else{
  //   Serial.println("Hubo un problema en la transmisión. Intentando en 5 segundos");
  //   delay(5000);
  // }
}