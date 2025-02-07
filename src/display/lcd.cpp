#include "lcd.h"

LCD::LCD(uint8_t addr, uint8_t cols, uint8_t rows) : lcd(addr, cols, rows) {}

void LCD::init()
{
    lcd.init();
    lcd.backlight();
}

// Display an error message on the LCD
void LCD::displayError(String message)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error: ");
    lcd.print(message);
}

// Display a message when WiFi is connected
void LCD::displayWifiConnected(String to)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Conected to: ");
    lcd.setCursor(0, 1);
    lcd.print(to);
    delay(2000);
}

// Display a message when WiFi is not connected
void LCD::displayWifiNotConnected(String ssid, String pass)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*Configure WiFi*");
    lcd.setCursor(0, 1);
    lcd.print(ssid);
    lcd.print(": ");
    lcd.print(pass);
}
// Display a welcome message on the LCD
void LCD::dispayWelcome()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ESP-Based IoT  ");
    lcd.setCursor(0, 1);
    lcd.print("Weather Station ");

    delay(2000);
}

void LCD::display(float rain, float temp, float humidity, float pressure, String pUnit)
{
    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 500; // Update every 500ms
    static unsigned long toggleTimer = 0;
    const unsigned long toggleInterval = 5000; // Toggle between sets every 5 seconds

    static bool showSet1 = true; // Toggle between two sets of data

    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= updateInterval)
    {
        lastUpdate = currentMillis; // Reset update timer

        if (currentMillis - toggleTimer >= toggleInterval)
        {
            toggleTimer = currentMillis; // Reset toggle timer
            showSet1 = !showSet1;        // Toggle between sets
        }

        if (showSet1)
        {
            // Show Temperature and Humidity
            lcd.setCursor(0, 0);
            lcd.print("Temp: ");
            lcd.print(temp);
            lcd.print(" C          ");

            lcd.setCursor(0, 1);
            lcd.print("Humid: ");
            lcd.print(humidity);
            lcd.print(" %          ");
        }
        else
        {
            // Show Pressure and Rain
            lcd.setCursor(0, 0);
            lcd.print("P: ");
            lcd.print(pressure);
            lcd.print(" ");
            lcd.print(pUnit);
            lcd.print("          ");

            lcd.setCursor(0, 1);
            lcd.print("Rain: ");
            lcd.print(rain);
            lcd.print(" mm          ");
        }
    }
}
