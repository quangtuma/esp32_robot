#include "esp32-hal.h"
#include "robot.h"

Robot::Robot()
{
#ifdef DEBUG_ON
  Serial.begin(SERIAL);
#endif
}
Robot::Robot(int *servosPin, int *servosRootPos)
{
#ifdef DEBUG_ON
  Serial.begin(SERIAL);
#endif
  for (int index = 0; index < SERVO_NUMBER; index++)
  {
    int *pointPin = servosPin + index;
    ServosPins[index] = *pointPin;
    int *pointPos = servosRootPos + index;
    ServosRootPos[index] = *pointPos;
  }
}
void Robot::begin()
{
  for (int index = 0; index < SERVO_NUMBER; index++)
  {
    Servos[index].attach(ServosPins[index]);
    Servos[index].write(ServosRootPos[index]);
#ifdef DEBUG_ON
    Serial.printf("Servos %d: ,pin: %d, pos: %d\n", index, ServosPins[index], ServosRootPos[index]);
#endif
  }
#ifdef DEBUG_ON
  Serial.println("Robot began.");
#endif
}
void Robot::runAutoServos()
{
  //Serial.println("INCREASE");
  for (int pos = 0; pos <= 29; pos++)
  {
    for (int index = 0; index < 3; index++)
    {
      calculatePostion(pos, index);
    }
  }

  delay(1000);

  //Serial.println("DECREASE");
  for (int pos = 29; pos >= 0; pos--)
  {
    for (int index = 2; index >= 0; index--)
    {
      calculatePostion(pos, index);
    }
  }
  
  delay(1000);
}

void Robot::runManualServos(int *servoPos)
{
  for (int index = 0; index < SERVO_NUMBER; index++)
  {
    int pos = *(servoPos + index);

    if (pos < ServosRootPosLimit[index][0])
      pos = ServosRootPosLimit[index][0];
    else if (pos > ServosRootPosLimit[index][1])
      pos = ServosRootPosLimit[index][1];

    //Servos[index].write(pos);
    runServo(pos, index);
#ifdef DEBUG_ON
    Serial.printf("Servos %d: ,pin: %d, pos: %d\n", index, ServosPins[index], pos);
#endif
  }
}

void Robot::runServo(int pos, int index)
{
  if (ServosCurrentPos[index] > pos)
    while (ServosCurrentPos[index] > pos)
    {
      ServosCurrentPos[index]--;
      Servos[index].write(ServosCurrentPos[index]);
      delay(10);
    }
  else if (ServosCurrentPos[index] < pos)
    while (ServosCurrentPos[index] < pos)
    {
      ServosCurrentPos[index]++;
      Servos[index].write(ServosCurrentPos[index]);
      delay(10);
    }
}

void Robot::calculatePostion(int pos, int index)
{
  int pos0 = ServosRootPos[0] + (pos * 3) + index;
  Servos[0].write(pos0);
  ServosCurrentPos[0] = pos0;

  int pos1 = ServosRootPos[1] + (pos * 3) + index;
  Servos[1].write(pos1);
  ServosCurrentPos[1] = pos1;

  int pos2 = ServosRootPos[2] - pos;
  Servos[2].write(pos2);
  ServosCurrentPos[2] = pos2;

  int pos3 = ServosRootPos[3] - (pos * 3) - index;
  Servos[3].write(pos3);
  ServosCurrentPos[0] = pos0;

  int pos4 = ServosRootPos[4] - (pos * 3) - index;
  Servos[4].write(pos4);
  ServosCurrentPos[4] = pos4;

  int pos5 = ServosRootPos[5] + pos;
  Servos[5].write(pos5);
  ServosCurrentPos[5] = pos5;

#ifdef DEBUG_ON
    Serial.printf("Pos: 0: %d, Pos: 1: %d, Pos: 2: %d, Pos: 3: %d, Pos: 4: %d, Pos: 5: %d\n", pos0, pos1, pos2, pos3, pos4, pos5);
#endif

  delay(15);
}
