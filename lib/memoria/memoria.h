#ifndef memoria_H
#define memoria_H

#include <Arduino.h>

// Liberias propias
#include <dhtLib.h>
#include <mqttConn.h>
#include <varGlobals.h>
#include <wifiConn.h>




bool saveConfig (void);
bool loadConfig (void);

#endif