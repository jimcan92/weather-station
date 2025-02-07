#ifndef GSHEET_H
#define GSHEET_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "sensors/rain.h"

extern RainGauge rainGauge;

class GSheet
{

public:
    GSheet(String url, int sendIntervalMin);
    void send(float rain, float temp, float humidity, float pressure, String pUnit);

private:
    void _send(float rain, float temp, float humidity, float pressure, String pUnit);
    String _url;
    int _sendIntervalMin;
};

#endif