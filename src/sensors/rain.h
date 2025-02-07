#ifndef RAIN_H
#define RAIN_H

#include <Arduino.h>

class RainGauge
{
public:
    RainGauge(int pin, float mmPerTip);
    void begin();
    float getRainfall();
    void handleTip();
    void reset();

private:
    int _rainCount;
    float _mmPerTip;
    int _pin;
    static void IRAM_ATTR isrHandler();
};

#endif
