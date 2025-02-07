#include "bmp.h"
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp280;

BMP280::BMP280(uint8_t address)
{
    _address = address;
}

bool BMP280::begin()
{
    return bmp280.begin(_address);
}

// Get the pressure based on the display unit (hPa, kPa, mmHg, atm, Torr, bar, Pa)
float BMP280::getPressure(float displayUnit)
{
    return bmp280.readPressure() / displayUnit;
}

// Get the pressure unit to display
String BMP280::getPUnit(float displayUnit)
{
    if (displayUnit == HPA)
    {
        return "hPa";
    }
    else if (displayUnit == KPA)
    {
        return "kPa";
    }
    else if (displayUnit == MMHG)
    {
        return "mmHg";
    }
    else if (displayUnit == ATM)
    {
        return "atm";
    }
    else if (displayUnit == TORR)
    {
        return "Torr";
    }
    else if (displayUnit == BAR)
    {
        return "bar";
    }
    else
    {
        return "Pa";
    }
}