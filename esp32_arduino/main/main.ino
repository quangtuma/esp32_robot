#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include "robot.h"

// Wifi information (SSID, Password)
const char* ssid = "Phi Long";
const char* password = "98765432";

// Mode infor url
String CONTROLLING_URL = "controlling";
String MODE_URL = "mode";

// URL connect to rest api server to get data from MongoDB
String URL = "http://192.168.1.97:3000/api/";
HTTPClient http;

// Struct to store MODE
typedef struct ServoMode {
  const char* id;
  int mode;
};

enum MODE_ENUM {
  AUTO = 0,
  MANUAL
};

ServoMode MODE;

// Struct to store Servo information from MongDB
typedef struct ServoInfor {
  const char* id;
  const char* servo;
  const char* description;
  int value;
};

// Array store Servos information from MongDB
ServoInfor ServoInfors[SERVO_NUMBER];

Robot ROBOT;

ServoMode getModeFromJson(String json) {
  char jsonChar[200];
  json.toCharArray(jsonChar, json.length() + 1);
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, jsonChar);

  ServoMode mode;
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());

    return mode;
  }
  mode.id = doc["_id"];
  mode.mode = doc["mode"];

  return mode;
}

ServoInfor getInforFromJson(String json) {
  char jsonChar[200];
  json.toCharArray(jsonChar, json.length() + 1);
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, jsonChar);

  ServoInfor servo;
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

String getOneJson(String jsons, int* startIndex) {
  // split json string from '{' to '}'
  *startIndex = jsons.indexOf('{', *startIndex);
  int lastIndex = jsons.indexOf('}', *startIndex) + 1;
  String json = jsons.substring(*startIndex, lastIndex);

  // assign next start index
  *startIndex = lastIndex;
  return json;
}

void httpRequest(String urlRequest) {
  http.begin(URL + urlRequest); // Specify the URL
  int httpCode = http.GET(); // Make the GET request
  
  if (httpCode > 0) 
  {
    // Check for a successful response
    //Serial.printf("[HTTP] %s GET... code: %d\n", urlRequest, httpCode);

    if (httpCode == HTTP_CODE_OK) {
      // Get the response payload
      String payload =  http.getString();

      // remove [] of response json string
      payload = payload.substring(1, payload.length() - 1);
      
      // index of '{', indexArray of ServoInfors, nextIndex of '}' + 1
      int startIndex = 0;
      
      if (urlRequest == MODE_URL)
      {
        String json = getOneJson(payload, &startIndex);
        MODE = getModeFromJson(json);
      }
      else if (urlRequest == CONTROLLING_URL)
      {
        int indexArray = 0; 
        // Print positions for debug
        // Serial.print("Pos ");
        while (startIndex < payload.length())
        {
          // get one json string from payload
          String json = getOneJson(payload, &startIndex);

          // get and store servo struct from one json
          ServoInfors[indexArray] = getInforFromJson(json);

          // Print positions for debug
          // int pos = ServoInfors[indexArray].value;
          // Serial.printf("%d = %d ", indexArray, pos);
          
          // index to next element in ServoInfors
          indexArray++;
        }
        // Print positions for debug
        // Serial.println(".");
      }
      else 
        Serial.printf("[HTTP] %s GET request wrong\n", urlRequest);
    }
  }
  else {
    Serial.printf("[HTTP] %s GET request failed, error: %s\n", urlRequest, http.errorToString(httpCode).c_str());
  }

  http.end(); // Close connection
}

void setupWifi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void setup() {

  Serial.begin(115200);

  ROBOT.begin();

  setupWifi();
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    httpRequest(MODE_URL);
    if (MODE.mode == MANUAL)
    {
      httpRequest(CONTROLLING_URL);
      
      int updating_pos[SERVO_NUMBER];

      for (int index = 0; index < SERVO_NUMBER; index++)
      {
        updating_pos[index] = ServoInfors[index].value;
      }

      // update last status of servos
      Serial.printf("ROBOT is in Manual Mode.\n");
      ROBOT.runManualServos(updating_pos);
    }
    else
    {
      Serial.printf("ROBOT is in Automactic Mode.\n");
      ROBOT.runAutoServos();
    }
  }
  else
  {
    Serial.printf("ROBOT is in Automactic Mode.\n");
    ROBOT.runAutoServos();
  }

  // delay to implement
  delay(3000); // Wait for 3 seconds before making the next request
}
