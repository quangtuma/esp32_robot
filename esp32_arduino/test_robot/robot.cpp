#include "robot.h"

namespace Robot
{
    void Robot::begin()
    {
      for (int index = 0; index < SERVO_NUMBER; index++)
      {
        Robot::Servos[index].attach(Robot::ServosPins[index]);
        Robot::Servos[index].write(Robot::ServosRootPos[index]);
      }
    }
    void Robot::updateServo()
    {
      //Serial.println("INCREASE");
      for (int pos = 0; pos <= 29; pos++)
      {
        for (int index = 0; index < 3; index++)
        {
          Robot::calculatePostion(pos, index);
        }
      }

      delay(1500);

      //Serial.println("DECREASE");
      for (int pos = 29; pos >= 0; pos--)
      {
        for (int index = 2; index >= 0; index--)
        {
          Robot::calculatePostion(pos, index);
        }
      }
    }
    void Robot::calculatePostion(int pos, int index)
    {
      int pos0 = Robot::ServosRootPos[0] + (pos * 3) + index;
      Robot::Servos[0].write(pos0);
      Robot::ServosCurrentPos[0] = pos0;

      int pos1 = Robot::ServosRootPos[1] + (pos * 3) + index;
      Robot::Servos[1].write(pos1);
      Robot::ServosCurrentPos[1] = pos1;

      int pos2 = Robot::ServosRootPos[2] - pos;
      Robot::Servos[2].write(pos2);
      Robot::ServosCurrentPos[2] = pos2;

      int pos3 = Robot::ServosRootPos[3] - (pos * 3) - index;
      Robot::Servos[3].write(pos3);
      Robot::ServosCurrentPos[0] = pos0;

      int pos4 = Robot::ServosRootPos[4] - (pos * 3) - index;
      Robot::Servos[4].write(pos4);
      Robot::ServosCurrentPos[4] = pos4;

      int pos5 = Robot::ServosRootPos[5] + pos;
      Robot::Servos[5].write(pos5);
      Robot::ServosCurrentPos[5] = pos5;
      delay(15);
    }
  }
}