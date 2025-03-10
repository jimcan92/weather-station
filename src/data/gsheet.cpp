#include "gsheet.h"

GSheet::GSheet(String url, int sendIntervalMin)
{
    _url = url;
    _sendIntervalMin = sendIntervalMin;
}

void GSheet::_send()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;

        String urlWithParams = _url;
        urlWithParams += "?temp=" + String(bmp.getTemperature());
        urlWithParams += "&humid=" + String(dht.readHumidity());
        urlWithParams += "&rain=" + String(rainGauge.getRainfall());
        urlWithParams += "&p=" + String(bmp.getPressure());
        urlWithParams += "&pUnit=" + bmp.getPUnit();

        http.begin(urlWithParams);

        int httpResponseCode = http.GET();

        if (httpResponseCode > 0)
        {
            Serial.println("Data sent successfully: " + String(httpResponseCode));
        }
        else
        {
            Serial.println("Error sending data: " + String(httpResponseCode));
        }

        http.end();
        rainGauge.reset();
    }
    else
    {
        Serial.println("WiFi not connected. Skipping data send.");
    }
}

void GSheet::send()
{
    static unsigned long lastSendTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastSendTime >= _sendIntervalMin * 60 * 1000)
    {
        lastSendTime = currentTime;
        _send();
    }
}