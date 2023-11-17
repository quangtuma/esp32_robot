// #include <ESP32Servo.h>

// #define SERVO_NUMBER 6

// Servo Servos[SERVO_NUMBER];
// int ServosPins[SERVO_NUMBER] = {13, 27, 33, 15, 16, 18}; // left - 13 27 33; right 15 16 18
// int ServosRootPos[SERVO_NUMBER] = {50, 17, 111, 167, 109, 125}; // left: 50+ 17+ -111+; right: 167- 109- -125+
// int ServosCurrentPos[SERVO_NUMBER];

// int ServosRootPosStaticMax[3] = {};
// int ServosRootPosStaticMin[3] = {};

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(115200);
//   for (int index = 0; index < SERVO_NUMBER; index++)
//   {
//     Servos[index].attach(ServosPins[index]);
//     Servos[index].write(ServosRootPos[index]);
//   }

//   delay(1500);
// }

// static void calculatePostion(int pos, int index)
// {
//   int pos0 = ServosRootPos[0] + (pos * 3) + index;
//   Servos[0].write(pos0);
//   ServosCurrentPos[0] = pos0;

//   int pos1 = ServosRootPos[1] + (pos * 3) + index;
//   Servos[1].write(pos1);
//   ServosCurrentPos[1] = pos1;

//   int pos2 = ServosRootPos[2] - pos;
//   Servos[2].write(pos2);
//   ServosCurrentPos[2] = pos2;

//   int pos3 = ServosRootPos[3] - (pos * 3) - index;
//   Servos[3].write(pos3);
//   ServosCurrentPos[0] = pos0;

//   int pos4 = ServosRootPos[4] - (pos * 3) - index;
//   Servos[4].write(pos4);
//   ServosCurrentPos[4] = pos4;

//   int pos5 = ServosRootPos[5] + pos;
//   Servos[5].write(pos5);
//   ServosCurrentPos[5] = pos5;

//   Serial.printf("pos 0: %d, pos 1: %d, pos 2: %d, pos 3: %d, pos 4: %d, pos 5: %d\n", pos0, pos1, pos2, pos3, pos4, pos5);
//   delay(15);
// }

// static void updateServo()
// {
//   Serial.println("INCREASE");
//   for (int pos = 0; pos <= 29; pos++)
//   {
//     for (int index = 0; index < 3; index++)
//     {
//       calculatePostion(pos, index);
//     }
//   }

//   delay(1500);

//   Serial.println("DECREASE");
//   for (int pos = 29; pos >= 0; pos--)
//   {
//     for (int index = 2; index >= 0; index--)
//     {
//       calculatePostion(pos, index);
//     }
//   }
//   // for (int index = 0; index < 3; index++)
//   // {
//   //   ServosCurrentPos[index] = ServosRootPos[index];
//   // }
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   updateServo();
//   delay(1500);
// }
