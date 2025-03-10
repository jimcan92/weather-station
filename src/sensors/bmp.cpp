#include "bmp.h"
#include <Adafruit_BMP280.h>

bool BMP280::begin()
{
    return _bmp280.begin(BMP_ADDR);
}

// Get the pressure based on the display unit (hPa, kPa, mmHg, atm, Torr, bar, Pa)
float BMP280::getPressure()
{
    return _bmp280.readPressure() / PRESSURE_UNIT;
}

// Get the pressure based on the display unit (hPa, kPa, mmHg, atm, Torr, bar, Pa)
float BMP280::getTemperature()
{
    return _bmp280.readTemperature();
}

// Get the pressure unit to display
String BMP280::getPUnit()
{
    if (PRESSURE_UNIT == HPA)
    {
        return "hPa";
    }
    else if (PRESSURE_UNIT == KPA)
    {
        return "kPa";
    }
    else if (PRESSURE_UNIT == MMHG)
    {
        return "mmHg";
    }
    else if (PRESSURE_UNIT == ATM)
    {
        return "atm";
    }
    else if (PRESSURE_UNIT == TORR)
    {
        return "Torr";
    }
    else if (PRESSURE_UNIT == BAR)
    {
        return "bar";
    }
    else
    {
        return "Pa";
    }
}