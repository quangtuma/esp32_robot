#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Van Cai";
const char* password = "88888888";
const char* url = "http://192.168.1.9:3000/api/controlling";

HTTPClient http;

struct ServoControlling
{
  const char* id;
  const char* servo;
  const char* description;
  const char* value;
};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  http.begin(url); // Specify the URL
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int httpCode = http.GET(); // Make the GET request

    if (httpCode > 0) { // Check for a successful response
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload =  http.getString(); // Get the response payload
        payload = payload.substring(1, payload.length() - 1);
        Serial.println(payload); // Print the payload

        char json[200];
        payload.toCharArray(json, payload.length() + 1);
        StaticJsonDocument<1000> doc;
        DeserializationError error = deserializeJson(doc, json);

        // Test if parsing succeeds.
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }

        ServoControlling servo;
        servo.id = doc["_id"];
        servo.servo = doc["servo"];
        Serial.println(servo.servo);
        servo.description = doc["description"];
        servo.value = doc["value"];
      }
    } else {
      Serial.printf("[HTTP] GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end(); // Close connection
  }

  delay(5000); // Wait for 5 seconds before making the next request
}
