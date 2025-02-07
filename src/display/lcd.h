#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCD
{
public:
    LCD(uint8_t addr, uint8_t cols, uint8_t rows);
    void init();
    void displayError(String message);
    void dispayWelcome();
    void displayWifiNotConnected(String ssid, String pass);
    void displayWifiConnected(String to);
    void display(float rain, float temp, float humidity, float pressure, String pUnit);

private:
    LiquidCrystal_I2C lcd;
};

#endif
