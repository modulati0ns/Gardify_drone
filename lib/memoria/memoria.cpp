#include <memoria.h>

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

bool shouldSaveConfig = 0; // 0 = guardar config; 1 = NO guardar config

bool saveConfig()
{
    //Parseado de char* a String
    String SSID = String(ssid);
    String pass = String(password);

    Serial.println("***************** ESCRITURA DE CONFIGURACION *******************");
    Serial.println("");
    if (shouldSaveConfig)
    {
        Serial.println("Almacenando los datos");

        // json["Frequency"] = Frequency;
        // json["Duty_Cycle"] = Duty_Cycle;
        File configFile = SPIFFS.open("/config.json", "w");
        if (!configFile)
        {
            Serial.println("Error: No se encontro archivo de configuración");
            return false;
        }
        else
        {
            DynamicJsonDocument jsonBuffer(1024);
            jsonBuffer["SSID"] = SSID;
            jsonBuffer["pass"] = pass;
            jsonBuffer["configured"] = configured;
            jsonBuffer["id"] = id;
            jsonBuffer["nombre"] = nombre;

            // serializeJsonPretty(jsonBuffer, Serial);
            serializeJson(jsonBuffer, configFile);
            Serial.println("");
            configFile.close();
            //end save
            return true;
        }
    }
    else
    {
        Serial.println("No es necesario almacenar los datos");
        Serial.println("");
        return false;
    }
}

bool loadConfig()
{
    //read configuration from FS json
    Serial.println("");
    Serial.println("");
    Serial.println("***************** LECTURA DE CONFIGURACION ***********************");
    Serial.println("");
    SPIFFS.begin(true);

    if (SPIFFS.begin())
    {
        Serial.println("Sistema de archivos montado");
        if (SPIFFS.exists("/config.json"))
        { // Comprobar existencia de config.json
            Serial.println("Archivo de configuracion encontrado");
            File configFile = SPIFFS.open("/config.json", "r"); // Abrir archivo Config.json
            if (configFile)
            {
                Serial.println("Archivo de configuración abierto"); // Congig.json abierto
                size_t size = configFile.size();                    // Calculo de memoria de config.json
                Serial.println("Memoria: " + String(size));
                std::unique_ptr<char[]> buf(new char[size]); // Reservado de dicha memoria
                configFile.readBytes(buf.get(), size);
                // Serial.println("ARCHIVOS:"+String(buf.get())); // Muestra de contenido archivo config.json
                DynamicJsonDocument jsonBuffer(1024);
                DeserializationError error = deserializeJson(jsonBuffer, buf.get());
                if (!error)
                {

                    // serializeJsonPretty(jsonBuffer, Serial);
                    Serial.println("Lectura de archivo correcta");
                    configured = jsonBuffer["configured"];
                    id = jsonBuffer["id"];
                    
                    String Nom = jsonBuffer["nombre"];
                    nombre = Nom;

                    String SSID = jsonBuffer["SSID"];
                    String pass = jsonBuffer["pass"];
                    //Parseado de String a char*
                    strcpy(ssid, SSID.c_str());
                    strcpy(password, pass.c_str());
 

                    Serial.println("");

                    return true;
                }
                else
                {
                    Serial.println("Error: Fallo de lectura de archivo de configuración");
                    Serial.println("");
                    return false;
                }
            }
            else
            {
                Serial.println("Error: Fallo de apertura del archivo de configuración");
                Serial.println("");
                return false;
            }
        }
        else
        {
            Serial.println("Error: No existe archivo de configuracion");
            return false;
        }
    }
    else
    {
        Serial.println("Error: Sistema de archivos no montado");
        return false;
    }
}