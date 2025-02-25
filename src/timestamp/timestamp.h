#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <Arduino.h>
#include "time.h"
#include <WiFi.h>

class Timestamp
{
public:
    void init();
    String getTimestamp();
};

#endif