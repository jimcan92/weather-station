#ifndef FIREBASE_H
#define FIREBASE_H

#include <Arduino.h>
#include <FirebaseClient.h>
#include <HTTPClient.h>
// #include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseJson.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#include "timestamp/timestamp.h"

#define API_KEY "AIzaSyDjLE4xfLweve2O3Pc5ILByDaMkWEX6AIA"
#define PROJECT_ID "esp-min-weather-station"
#define COLLECTION "weather-data"

#define ADMIN_EMAIL "admin@esp.weather.com"
#define ADMIN_PASS "admin007"

#define SEND_INTERVAL 1 // X minute

extern Timestamp timestamp;

struct FirestoreData
{
    float temp;
    float humid;
};

class FirebaseFirestore
{
public:
    void send(FirestoreData data);
    void sendEvery(FirestoreData data);

private:
    String getIdToken(String email, String pass);
};

#endif