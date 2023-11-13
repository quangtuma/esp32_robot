#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

#define SERVO_LEFT_THIGH 13
#define SERVO_LEFT_KNEE 12
#define SERVO_LEFT_ANKLE 14
#define SERVO_RIGHT_THIGH 27
#define SERVO_RIGHT_KNEE 26
#define SERVO_RIGHT_ANKLE 25
#define SERVO_NUMBER 6

const char* ssid = "Cafe";
const char* password = "phamnhuxuong";
const char* url = "http://192.168.1.4:3000/api/controlling";

struct ServoControlling
{
  const char* id;
  const char* servo;
  const char* description;
  const char* value;
};


HTTPClient http;
ServoControlling ControllingArray[SERVO_NUMBER];
Servo ServoObjects[SERVO_NUMBER];

ServoControlling getStructFromJson(String json)
{
  char jsonChar[200];
  json.toCharArray(jsonChar, json.length() + 1);
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
  servo.description = doc["description"];
  servo.value = doc["value"];

  return servo;
}

String getOneJson(String jsons, int* startIndex)
{
  *startIndex = jsons.indexOf('{', *startIndex);
  int lastIndex = jsons.indexOf('}', *startIndex) + 1;

  String json = jsons.substring(*startIndex, lastIndex);

  *startIndex = lastIndex;

  return json;
}

void setupServos()
{
  ServoObjects[0].attach(SERVO_LEFT_THIGH);
  ServoObjects[1].attach(SERVO_LEFT_KNEE);
  ServoObjects[2].attach(SERVO_LEFT_ANKLE);
  ServoObjects[3].attach(SERVO_RIGHT_THIGH);
  ServoObjects[4].attach(SERVO_RIGHT_KNEE);
  ServoObjects[5].attach(SERVO_RIGHT_ANKLE);
}

void updateServo()
{
  for (int index = 0; index < SERVO_NUMBER; index++)
  {
    int pos = strtol(ControllingArray[index].value, NULL, 10);
    if (pos < 0 || pos > 180)
      Serial.println("Pos is over range from 0 degree to 180 degree!");
    else 
      ServoObjects[index].write(pos);
  }
}

void setup() {
  Serial.begin(115200);

  setupServos();

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
        //Serial.println(payload);
        
        // index of '{', indexArray of ControllingArray, nextIndex of '}' + 1
        int indexArray, startIndex = 0;

        while (startIndex < payload.length())
        {
          String json = getOneJson(payload, &startIndex);
          ControllingArray[indexArray] = getStructFromJson(json);

          Serial.print("ControllingArray: ");
          Serial.println(ControllingArray[indexArray].value);
          Serial.println(typeid(ControllingArray[indexArray].value).name);
          //int pos = ControllingArray[indexArray].value;
          //Serial.print("Pos: ");
          //Serial.println(pos);
          
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
