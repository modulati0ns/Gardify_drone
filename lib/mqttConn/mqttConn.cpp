#include <mqttConn.h>

#include <Arduino.h>
#include <PubSubClient.h>

bool lastSendStatus; // 0 = envio correcto; 1 = envio incorrecto

bool sendData()
{
  Serial.println("ENVIANDO DATOS POR MQTT");
  Serial.println("");
  
//   dataToSend.temperatura = temperatura;
//   dataToSend.humedadaire = humedadaire;
//   dataToSend.id = ESP.getChipId();



  // PRINT NAME
//   Serial.print("Nombre: ");
//   for (int i = 0; i < strlen(nombre); i++)
//   {
//     dataToSend.nombre[i] = nombre[i];
//     Serial.print(nombre[i]);
//   }
//   Serial.println("");

  // Ejecuta el envío
  

  if (lastSendStatus == 0){
    return true;
  }else{
    return false;
  }
}
