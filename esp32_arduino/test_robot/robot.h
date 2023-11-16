#include <ESP32Servo.h>

#define SERVO_NUMBER 6
#define SERVO_LEFT_THIGH 13
#define SERVO_LEFT_KNEE 27
#define SERVO_LEFT_ANKLE 33
#define SERVO_RIGHT_THIGH 15
#define SERVO_RIGHT_KNEE 16
#define SERVO_RIGHT_ANKLE 18

namespace Robot
{
  Servo Servos[SERVO_NUMBER];
  int ServosPins[SERVO_NUMBER] = {13, 27, 33, 15, 16, 18}; // left - 13 27 33; right 15 16 18
  int ServosRootPos[SERVO_NUMBER] = {50, 17, 111, 167, 109, 125}; // left: 50+ 17+ -111+; right: 167- 109- -125+
  int ServosCurrentPos[SERVO_NUMBER];
  class Robot
  {
    public:
      static void begin();
      static void updateServo();
    private:
      static void calculatePostion(int pos, int index);
  }
}
