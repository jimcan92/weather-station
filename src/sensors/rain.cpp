#include "rain.h"

volatile int rainCount = 0;

RainGauge::RainGauge(int pin, float mmPerTip)
{
    _mmPerTip = mmPerTip;
    _pin = pin;
    _rainCount = 0;
}

void RainGauge::begin()
{
    pinMode(_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(_pin), RainGauge::isrHandler, FALLING);
}

void IRAM_ATTR RainGauge::isrHandler()
{
    static uint32_t lastInterruptTime = 0;
    uint32_t currentTime = millis();

    if (currentTime - lastInterruptTime > 100) // 100ms debounce time
    {
        rainCount++; // Register only one tip
        lastInterruptTime = currentTime;
    }
}

void RainGauge::handleTip()
{
    _rainCount = rainCount;
}

// Get the amount of rainfall in mm
float RainGauge::getRainfall()
{
    return _rainCount * _mmPerTip;
}

void RainGauge::reset()
{
    rainCount = 0;
    _rainCount = 0;
}
