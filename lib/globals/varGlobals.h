#ifndef varGlobals_H
#define varGlobals_H

#include<Arduino.h>

// Liberias propias
#include <dhtLib.h>
#include <mqttConn.h>
#include <memoria.h>
#include <wifiConn.h>


// VARIABLES SMART GARDEN
extern float temperatura; // Variable de la temperatura
extern float humedadaire; // Variable de la humedad del aire
extern bool configured;
extern bool lastSendStatus;
extern bool shouldSaveConfig;
extern int id;
extern String nombre;

extern char ssid[40];
extern char password[40];

// typedef struct struct_message {
//   uint8_t droneAddress[6];
//   int id;
//   char nombre[];
//   float temperatura;
//   float humedadaire;
// } struct_message;

// extern const char *nombrea;

// extern struct struct_message dataToSend;
// extern uint8_t broadcastAddress[];
// extern uint8_t broadcastAddress1[];
extern uint8_t droneAddress[6];




#endif