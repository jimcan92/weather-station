#include <Arduino.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <DHT.h>

#include "sensors/bmp.h"
#include "data/gsheet.h"
#include "sensors/rain.h"
#include "display/lcd.h"

#define USE_SERIAL 1 // Set to 1 to enable serial output 0 to disable

// Set the SSID and password of the ESP32 Access Point
#define WIFI_AP_SSID "ESPW"
#define WIFI_AP_PASS "00000007"

// LCD settings
#define LCD_COLS 16   // Number of columns in the LCD
#define LCD_ROWS 2    // Number of rows in the LCD
#define LCD_ADDR 0x27 // I2C address of the LCD

// BMP280 sensor settings
#define BMP_ADDR 0x76     // BMP280 I2C address
#define PRESSURE_UNIT ATM // Pressure unit to display

// Google Sheets settings
#define WEBHOOK_URL "https://script.google.com/macros/s/AKfycbyO8JsoQ0hcT7YTWrPdCoYI7YPfHXzIGawrk7NTIdx3ujDFkxTYKeBPPkDfKWZ1HlgSrA/exec"
#define SEND_INTERVAL_MIN 1 // send data to google sheets every X min

// Rain gauge settings
#define RAIN_PIN 23       // Rain gauge input pin
#define MM_PER_TIP 0.2794 // mm of rain per tip

// DHT sensor settings
#define DHT_PIN 4      // DHT sensor input pin
#define DHT_TYPE DHT22 // DHT sensor type

// Temperature offset
#define TEMP_OFFSET -3.0F // Calibration offset for temperature in Celsius

RainGauge rainGauge(RAIN_PIN, MM_PER_TIP);
LCD lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
BMP280 bmp(BMP_ADDR);
DHT dht(DHT_PIN, DHT_TYPE);
GSheet gsheet(WEBHOOK_URL, SEND_INTERVAL_MIN);

void setupWifi()
{
  WiFiManager wm;

  // wm.resetSettings(); // Uncomment to reset WiFi settings

  bool connected = false;

  while (!connected)
  {
    lcd.displayWifiNotConnected(WIFI_AP_SSID, WIFI_AP_PASS);
    connected = wm.autoConnect(WIFI_AP_SSID, WIFI_AP_PASS);
  }

  lcd.displayWifiConnected(WiFi.SSID());
}

void setup()
{
#if USE_SERIAL
  Serial.begin(115200);
#endif

  lcd.init();
  lcd.dispayWelcome();

  setupWifi();

  rainGauge.begin();
  dht.begin();

  if (!bmp.begin())
  {
#if USE_SERIAL
    Serial.println("BMP280 not detected!");
#endif

    lcd.displayError("BMP280 not detected!");
    delay(2000);
  }
}

void loop()
{
  rainGauge.handleTip();
  lcd.display(
      rainGauge.getRainfall(),
      dht.readTemperature() + TEMP_OFFSET,
      dht.readHumidity(),
      bmp.getPressure(PRESSURE_UNIT),
      bmp.getPUnit(PRESSURE_UNIT));
  gsheet.send(
      rainGauge.getRainfall(),
      dht.readTemperature() + TEMP_OFFSET,
      dht.readHumidity(),
      bmp.getPressure(PRESSURE_UNIT),
      bmp.getPUnit(PRESSURE_UNIT));
}
