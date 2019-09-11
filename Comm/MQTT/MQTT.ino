#include <WiFi.h>
#include <PubSubClient.h>


const char*  ssid="Emprendedores";
const char* password= "AxtVvm13";
const char* mqtt_server="192.168.1.197";
const int pinCell=5;

WiFiClient wifi;
PubSubClient client(wifi);

long lasMsg=0;
char msg[25];

void connectToNetwork()
{
    WiFi.begin(ssid,password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Estableciendo conexión...");
    }

    Serial.println("Conectado");
    
}

void callback(char* topic, byte* message, unsigned int length)
{
    Serial.println("A llegado un mensaje");
    Serial.print("Asunto: ");
    Serial.print(topic);
    Serial.print("Mensaje: ");
    String incoming;

    for (int i = 0; i < length; i++)
    {
         Serial.print((char)message[i]);
         incoming += (char)message[i];
    }

    Serial.println();
}

void reconnect()
{
    while(!client.connected())
    {
        if (client.connected())
        {
            Serial.println("conectado");
            client.subscribe("esp32/pinCell/output");
           
        }
        else
        {
            Serial.print("Conexion Fallida ");
            Serial.print(client.state());
            delay(3000);

        }
    }
}

void setup()
{
    Serial.begin(115200);
    connectToNetwork();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lasMsg > 3000)
    {
        /* code of read data FotoCell */
        char value[8];
        dtostrf(analogRead(pinCell),1, 2, value);
        //dtostrf()
        client.publish("esp32/fotocell/output", value);
    }
    
}
