#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include <ESP32Servo.h>

#define DEBUG

#define SERIAL 115200
#define SERVO_NUMBER 6
#define FOOT_NUMBER 2

// define defaul pin of servos
#define SERVO_LEFT_THIGH_PIN 13
#define SERVO_LEFT_KNEE_PIN 27
#define SERVO_LEFT_ANKLE_PIN 33
#define SERVO_RIGHT_THIGH_PIN 15
#define SERVO_RIGHT_KNEE_PIN 16
#define SERVO_RIGHT_ANKLE_PIN 18

// define root position of servos
#define SERVO_LEFT_THIGH_ROOT_POS 50
#define SERVO_LEFT_KNEE_ROOT_POS 17
#define SERVO_LEFT_ANKLE_ROOT_POS 111
#define SERVO_RIGHT_THIGH_ROOT_POS 167
#define SERVO_RIGHT_KNEE_ROOT_POS 109
#define SERVO_RIGHT_ANKLE_ROOT_POS 125

class Robot
{

  public:
    Robot();
    Robot(int *servosPin, int *servosRootPos);
    void begin();
    void runAutoServos();
    void runManualServos(int *servoPos);
  private:
    void calculatePostion(int pos, int index);
    Servo Servos[SERVO_NUMBER];
    int ServosPins[SERVO_NUMBER] = 
    {
      SERVO_LEFT_THIGH_PIN, SERVO_LEFT_KNEE_PIN, SERVO_LEFT_ANKLE_PIN, 
      SERVO_RIGHT_THIGH_PIN, SERVO_RIGHT_KNEE_PIN, SERVO_RIGHT_ANKLE_PIN 
    }; // left - 13 27 33; right 15 16 18

    int ServosRootPos[SERVO_NUMBER] = {
      SERVO_LEFT_THIGH_ROOT_POS, SERVO_LEFT_KNEE_ROOT_POS, SERVO_LEFT_ANKLE_ROOT_POS, 
      SERVO_RIGHT_THIGH_ROOT_POS, SERVO_RIGHT_KNEE_ROOT_POS, SERVO_RIGHT_ANKLE_ROOT_POS 
    }; // left: 50+ 17+ -111+; right: 167- 109- -125+

    int ServosRootPosLimit[SERVO_NUMBER][FOOT_NUMBER] =
    {
      { 50, 140 }, { 17, 127 }, { 71, 151 },
      { 77, 167 }, { 0, 110 }, { 85, 165 }
    };

    int ServosCurrentPos[SERVO_NUMBER];
};

#endif
