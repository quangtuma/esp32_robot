#include "robot.h"

int ServosRootPos[SERVO_NUMBER] = {88, 12, 70, 180, 100, 95}; // left: 50+ 17+ -111+; right: 167- 109- -125+

Robot robot;

void setup()
{
  Serial.begin(115200);
  robot.begin();
}

void loop()
{
  //robot.runAutoServos();
  robot.runAutoServos();
  delay(5000);
  robot.runManualServos(ServosRootPos);
  delay(5000);
}