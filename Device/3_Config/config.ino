#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <DNSServer.h>
#include <WiFiManager.h>

const int PIN_AP = 2;

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_AP,INPUT);

    WiFiManager wifiManager;

   // wifiManager.setAPCallback(configModeCallback);
   // wifiManager.setSaveConfigCallback(configModeCallback);
    
    wifiManager.autoConnect("HHESP32","1234");

}

void loop()
{
     WiFiManager wifiManager;
     if (digitalRead(PIN_AP)== HIGH)
     {
         if (!wifiManager.startConfigPortal("HHESP32","1234"))
         {
            delay(2000);
            ESP.restart();
            delay(2000);
         }
         
     }
}
     
/*void configModeCallback(wifiManager *myWiFiManager)
{
    Serial.println("Modo de configuración...");
    Serial.println(WiFi.softAPIP());
    serial.println(myWiFiManager->getConfigPortalSSID());
}

void saveConfigCallback()
{
    Serial.println("Configuración guardada"); 
    Serial.println(WiFi.softAPIP());   
}

}*/



