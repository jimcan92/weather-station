#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#include "sensors/rain.h"
#include "sensors/bmp.h"

extern RainGauge rainGauge;
extern BMP280 bmp;
extern DHT dht;

class LCD
{
public:
    LCD(uint8_t addr, uint8_t cols, uint8_t rows);
    void init();
    void displayError(String message);
    void dispayWelcome();
    void displayWifiNotConnected(String ssid, String pass);
    void displayWifiConnected(String to);
    void display();

private:
    LiquidCrystal_I2C lcd;
};

#endif
