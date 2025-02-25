#include "timestamp.h"

const char *ntpServer = "time.google.com";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 0;

void Timestamp::init()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi not connected!");
        return;
    }

    Serial.println("Syncing time...");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    struct tm timeinfo;
    for (int i = 0; i < 10; i++)
    { // Try 10 times
        if (getLocalTime(&timeinfo))
        {
            Serial.println("Time synchronized!");
            return;
        }
        Serial.println("Retrying NTP sync...");
        delay(500); // Wait for NTP sync
    }

    Serial.println("Failed to sync time!");
}

String Timestamp::getTimestamp()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return "";
    }

    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
    return String(timestamp);
}
