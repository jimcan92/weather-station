#ifndef GSHEET_H
#define GSHEET_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#include "sensors/rain.h"
#include "sensors/bmp.h"

extern RainGauge rainGauge;
extern BMP280 bmp;
extern DHT dht;

class GSheet
{

public:
    GSheet(String url, int sendIntervalMin);
    void send();

private:
    void _send();
    String _url;
    int _sendIntervalMin;
};

#endif