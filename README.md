# SmartSkies: A Sustainable IoT Weather Station for Community-Based Climate

This project is an ESP32-based weather station that measures and logs temperature, humidity, pressure, and rainfall data. The collected data is sent to Google Sheets using Google Apps Script. Additionally, a web feature using SvelteKit, Firebase, and DaisyUI is hosted for free at [espweather.vercel.app](https://espweather.vercel.app).

## Features

- 📡 **Wi-Fi Connectivity**: Connects to Wi-Fi and logs data online.
- 🌡 **Temperature Sensor**: Measures ambient temperature.
- 💧 **Humidity Sensor**: Captures humidity levels.
- 🌦 **Rain Gauge**: Uses a tipping bucket mechanism to measure rainfall.
- 🌪 **Pressure Sensor**: Reads atmospheric pressure.
- 🔋 **Solar-Powered**: Uses a CN3065 mini solar charger with a 18650 battery and CE8301 boost converter.
- 📊 **Data Logging**: Stores data in Google Sheets.
- 🖥 **Web Dashboard**: Monitor weather data in real time at [espweather.vercel.app](https://espweather.vercel.app).
- 🖨 **3D-Printed Enclosures**: Custom enclosures for the solar power system and sensor housing.

## Hardware Requirements

- ESP32
- DHT22 (Temperature & Humidity Sensor)
- BMP280 (Pressure Sensor)
- Tipping Bucket Rain Gauge
- I2C LCD Display (Optional)
- CN3065 Mini Solar Charger
- 18650 Battery
- CE8301 Boost Converter
- 3D-Printed Enclosures

## Software Requirements

- PlatformIO in Visual Studio Code
- Libraries:
  - `WiFiManager` by tzapu
  - `LiquidCrystal_I2C`
  - `DHT Sensor library` by Adafruit
  - `Adafruit BMP280 Library` by Adafruit
  - `HTTPClient.h`
- Google Apps Script (for Google Sheets integration)
- Firestore (for cloud configuration storage)
- SvelteKit, Firebase, and DaisyUI (for the web dashboard)

## Setup Instructions

### 1. Install Required Libraries

Ensure you have the necessary libraries installed in PlatformIO. Use the `platformio.ini` file to include dependencies.

### 2. Configure and Upload ESP32 Code

1. Upload the firmware to the ESP32 using PlatformIO.
2. Monitor the Serial Monitor for connection and data transmission logs.

### 3. First-Time Wi-Fi Configuration

If the device does not detect any saved Wi-Fi credentials, it will create an access point with the following details:

- **SSID:** `ESPW`
- **Password:** `00000007`

On the LCD display, it will show:

```
ESPW: 00000007
```

Connect to this access point using a phone or computer, and follow the on-screen instructions to configure your Wi-Fi connection.

### 4. 3D-Printed Enclosures

The project includes 3D-printed enclosures for the solar power system and sensor housing. STL files that are available:

- [Solar Power Enclosure](3d_models/solar_enclosure.stl)
- [Sensor Housing](3d_models/sensor_housing.stl)
- [Connector for Enclosures](3d_models/connector.stl)

## Usage

- The ESP32 collects data at regular intervals (e.g., every minute) and sends it to Google Sheets.
- Data is saved in daily sheets (e.g., `Feb-02`, `Feb-03`, etc.).
- Weather data is accessible online at [espweather.vercel.app](https://espweather.vercel.app).
- Firestore stores configuration settings, which the ESP32 can fetch and apply dynamically.

## Troubleshooting

- **Wi-Fi Not Connecting?** Ensure correct credentials and check network strength.
- **Data Not Logging?** Check Apps Script logs and ESP32 serial monitor.
- **Battery Draining Quickly?** Check solar charging status and optimize power usage.

## Future Enhancements

- 📡 MQTT for real-time data streaming
- 🌎 Web dashboard for better visualization
- 🔄 Deep sleep mode for power efficiency
- 📈 AppSheet integration for data visualization
- 🛠 Cloud-based sensor calibration via Firestore

## License

This project is open-source under the MIT License.
