#include "firebase.h"

String FirebaseFirestore::getIdToken(String email, String pass)
{
    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure();

    String url = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" API_KEY;
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");

    String requestBody = "{";
    requestBody += "\"email\":\"";
    requestBody += email;
    requestBody += "\",\"password\":\"";
    requestBody += pass;
    requestBody += "\",\"returnSecureToken\":true";
    requestBody += "}";

    int httpResponseCode = http.POST(requestBody);

    String response = http.getString();
    http.end();

    if (httpResponseCode == 200)
    {
        JsonDocument doc; // Allocate enough space
        DeserializationError error = deserializeJson(doc, response);

        if (error)
        {
            Serial.print("JSON Parsing Error: ");
            Serial.println(error.f_str());
            return "";
        }

        if (doc["idToken"].is<String>())
        {
            String idToken = doc["idToken"].as<String>();
            return idToken;
        }
        else
        {
            Serial.println("idToken not found in response!");
            return "";
        }
    }
    else
    {
        Serial.println("Failed to get token");
        return "";
    }
}

void FirebaseFirestore::send(FirestoreData data)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi not connected!");
        return;
    }

    String idToken = getIdToken(ADMIN_EMAIL, ADMIN_PASS);

    if (idToken == "")
    {
        Serial.println("Failed to get idToken!");
        return;
    }

    String ts = timestamp.getTimestamp();

    if (ts == "")
    {
        Serial.println("Failed to get timestamp!");
        return;
    }

    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure();

    String url = "https://firestore.googleapis.com/v1/projects/" PROJECT_ID "/databases/(default)/documents/" COLLECTION;

    String authHeader = "Bearer ";
    authHeader += idToken;

    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", authHeader);

    // Create JSON data
    JsonDocument jsonDoc;
    jsonDoc["fields"]["temperature"]["doubleValue"] = data.temp;
    jsonDoc["fields"]["humidity"]["doubleValue"] = data.humid;
    jsonDoc["fields"]["timestamp"]["timestampValue"] = ts; // Replace with actual time

    String jsonData;
    serializeJson(jsonDoc, jsonData);

    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0)
    {
        Serial.println("Data sent successfully!");
    }
    else
    {
        Serial.printf("Error sending data: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
}

void FirebaseFirestore::sendEvery(FirestoreData data)
{
    static unsigned long lastSendTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastSendTime > SEND_INTERVAL * 60000) //
    {
        lastSendTime = currentTime;
        send(data);
    }
}