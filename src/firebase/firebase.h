#ifndef FIREBASE_H
#define FIREBASE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <DHT.h>

#include "timestamp/timestamp.h"
#include "sensors/rain.h"
#include "sensors/bmp.h"

#define API_KEY "AIzaSyDjLE4xfLweve2O3Pc5ILByDaMkWEX6AIA"
#define PROJECT_ID "esp-min-weather-station"
#define COLLECTION "weather-data"

#define ADMIN_EMAIL "admin@esp.weather.com"
#define ADMIN_PASS "admin007"

#define SEND_INTERVAL 1 // X minute

struct FirestoreData
{
    float temp;
    float humid;
    float pressure;
    float rain;
    String pressureUnit;
};

extern RainGauge rainGauge;
extern Timestamp timestamp;
extern BMP280 bmp;
extern DHT dht;

class FirebaseFirestore
{
public:
    void send();

private:
    void _send();
    String getIdToken(String email, String pass);
};

#endif