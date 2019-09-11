
void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.ptrintln("Hola desde ESP32");
    delay(2000);
}