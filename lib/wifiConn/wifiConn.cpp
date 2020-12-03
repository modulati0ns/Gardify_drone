#include <wifiConn.h>

#include <Arduino.h>
// #include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <SPIFFS.h>
// #define SPIFFS LittleFS

char ssid[40];
char password[40];


const char *ssidESP = "Gardify";
const char *passwordESP = "adminGardify";

AsyncWebServer server(80);

void wifiServer(void)
{
    WiFi.mode(WIFI_AP_STA); // Modo ESP-NOW y AP
    WiFi.softAP(ssidESP, NULL, 2);


    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", String(), false);
    });

    server.on("/action_page", HTTP_GET, [](AsyncWebServerRequest *request) {

        if (request->hasParam("nombre") && request->hasParam("ssid") && request->hasParam("password"))
        {

            // Parseador
            AsyncWebParameter *n = request->getParam(0);
            nombre = n->value();
            AsyncWebParameter *s = request->getParam(1);
            //ssid = s->value().c_str();
            strcpy(ssid, s->value().c_str());
            AsyncWebParameter *p = request->getParam(2);
            // password = p->value().c_str();
            strcpy(password,  p->value().c_str());

            // intento de conexion a internet con los datos introducidos
            WiFi.begin(ssid, password);
            while (WiFi.status() != WL_CONNECTED)
            {
                Serial.print('.');
                delay(500);
            }

            if (WiFi.status() == WL_CONNECTED)
            {
                // Ha habido un intento de conexion correcta y se deben almacenar los datos
                Serial.println("Conexión correcta");
                configured = 1;
                id = abs(ESP.getEfuseMac());
                shouldSaveConfig = true;
                saveConfig();
                request->send(200, "text/html", "A DISFRUTAR!");
            }
            else
            {
                // La primera conexion ha sido fallida y se debe volver a poner el emisor
                Serial.println("No se ha recibido conexion en el intento de configuracion");
                shouldSaveConfig = false;
                // Poner aqui HTML al que acceder en caso de conexion fallida
                configured = 0;
            }
        }
        else
        {
            Serial.print("NO HAY UNO ");
        }
    });

    server.begin();
}
