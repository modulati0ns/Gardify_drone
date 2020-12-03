#ifndef dhtLib_H
#define dhtLib_H

#include <Arduino.h>

// Liberias propias
#include <mqttConn.h>
#include <memoria.h>
#include <varGlobals.h>
#include <wifiConn.h>


extern float temperatura;
extern float humedadaire;

void dhtBegin(void);
void lecturaSensor(void);


#endif