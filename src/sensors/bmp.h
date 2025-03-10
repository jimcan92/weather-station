#ifndef BMP280_H
#define BMP280_H

#include <Arduino.h>
#include <Adafruit_BMP280.h>

#define BMP_ADDR 0x76     // BMP280 I2C address
#define PRESSURE_UNIT ATM // Pressure unit to display

#define HPA 100.0F    // 1 hPa = 100 Pa
#define KPA 1000.0F   // 1 kPa = 1000 Pa
#define MMHG 133.322F // 1 mmHg = 133.322 Pa
#define ATM 101325.0F // 1 atm = 101325 Pa
#define TORR 133.322F // 1 Torr = 133.322 Pa (same as mmHg)
#define BAR 100000.0F // 1 bar = 100000 Pa

class BMP280
{
public:
    bool begin();
    float getPressure();
    String getPUnit();
    float getTemperature();

private:
    Adafruit_BMP280 _bmp280;
};

#endif
