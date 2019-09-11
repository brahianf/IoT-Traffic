#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEAdvertisedDevice.h>
#include <BLEScan.h>

#define SERVICE_UUID "4d5d92c3-7ff7-4044-acce-0f6bbf6bb901"
#define CHARACTERISTIC_UUID "33423ede-8229-42fb-adb4-8484e298f5e5"

int scanTime = 3;
BLEScan  *bleScan;

class myBLEDeviceCallback: public BLEAdvertisedDevice
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        Serial.printf("Dispositivo: %s %s", advertisedDevice.toString().c_str(), String(advertisedDevice.getRSSI.c_str()));
    }
};

void setup()
{
    BLEDevice::init("BLE ESP32 HH");
    bleScan= BLEDevice::getScan();
    bleScan->setActiveScan(true);
    bleScan->setInterval(100);
    bleScan->setAdvertisedDeviceCallbacks(new myBLEDeviceCallback());
    bleScan->setWindow(99);
}

void loop()
{
    BLEScanResults foundDevices= bleScan->start(scanTime, false);
    Serial.println(foundDevices.getCount());
    bleScan->clearResults();
    delay (5000);
}

// void setup()
// {
//     Serial.begin(115200);
//     Serial.print("BLE inciando...");

//     BLEDevice::init("BLE ESP32 HH");
//     BLEServer *bleServer = BLEDevice::createServer();
//     BLEService *bleService = bleServer->createService(SERVICE_UUID);
//     BLECharacteristic *bleCharacteristic = bleService->createCharacteristic(CHARACTERISTIC_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

//     bleCharacteristic->setValue("Hola dispositivo ble");
//     bleService->start();

//     BLEAdvertising *bleAvertising = BLEDevice::getAdvertising();
//     bleAvertising-> addServiceUUID(SERVICE_UUID);
//     bleAvertising-> setScanResponse(true);
//     bleAvertising-> setMinPreferred(0x06);
//     BLEDevice::startAdvertising();
//     Serial.println("Ahora me puedo conectar");

// }

void loop(){}