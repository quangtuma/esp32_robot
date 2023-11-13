#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Phi Long";
const char* password = "98765432";
const char* url = "http://192.168.1.100:3000/api/controlling";

HTTPClient http;

struct ServoControlling
{
  const char* id;
  const char* servo;
  const char* description;
  const char* value;
};

ServoControlling ControllingArray[3];

ServoControlling getStructFromJson(String json)
{
  char jsonChar[200];
  json.toCharArray(jsonChar, json.length());
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, jsonChar);

  ServoControlling servo;
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());

    return servo;
  }
  servo.id = doc["_id"];
  servo.servo = doc["servo"];
  Serial.println(servo.servo);
  servo.description = doc["description"];
  servo.value = doc["value"];

  return servo;
}

String getOneJson(int startIndex, String jsons, int* nextIndex)
{
  int lastIndex = jsons.indexOf('}', startIndex);
  Serial.printf("lastIndex: %d\n", lastIndex);
  nextIndex = &lastIndex;
  Serial.printf("*nextIndex: %d\n", *nextIndex);
  return jsons.substring(startIndex, lastIndex);
}

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

        // remove [] of response json string
        payload = payload.substring(1, payload.length() - 1);
        Serial.println(payload);
        
        // index of '{', indexArray of ControllingArray, nextIndex of '}' + 1
        int index = 0;
        int indexArray = 0;
        int *nextIndex = 0;
        while (index < payload.length())
        {
          Serial.printf("index: %d\n", payload);
          // String json = getOneJson(index, payload, nextIndex);
          // Serial.printf("Json String: %s\n", json);
          // ControllingArray[indexArray] = getStructFromJson(json);
          // Serial.println("json: %s\n nextIndex: %d\n ControllingArray[indexArray].value: %s", json, *nextIndex,  ControllingArray[indexArray].value);
          index = *nextIndex + 1;
          indexArray++;
        }
      }
    } else {
      Serial.printf("[HTTP] GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end(); // Close connection
  }

  delay(3000); // Wait for 5 seconds before making the next request
}
