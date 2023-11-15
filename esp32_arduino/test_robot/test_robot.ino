#include <ESP32Servo.h>

Servo myServo[3];
int myServoPin[3] = {13, 27, 33};
int myServoPos[3] = {50, 17, 111};

void setup() {
  // put your setup code here, to run once:
  //myServo.attach(13);
  Serial.begin(115200);
  for (int index = 0; index < 3; index++)
  {
    myServo[index].attach(myServoPin[index]);
    myServo[index].write(myServoPos[index]);
  }
  //myServo.write(113);
}

void updateServo()
{
  delay(1500);

  Serial.println("INCREASE");
  for (int pos = 0; pos <= 29; pos++)
  {
    for (int index = 0; index < 3; index++)
    {
      int pos1 = myServoPos[1] + pos + index;
      myServo[1].write(pos1);
      int pos2 = myServoPos[2] - pos;
      myServo[2].write(pos2);
      delay(15);
    }
    // int pos1 = myServoPos[1] + pos * 3;
    // myServo[1].write(pos1);
    // int pos2 = myServoPos[2] - pos;
    // myServo[2].write(pos2);
    // //Serial.printf("pos 1: %d, pos 2: %d\n", pos1, pos2);
    
    // delay(15);
  }

  delay(1500);

  Serial.println("DECREASE");
  for (int pos = 29; pos >= 0; pos--)
  {
    int pos1 = myServoPos[1] + pos * 3;
    myServo[1].write(pos1);+
    int pos2 = myServoPos[2] - pos;
    myServo[2].write(pos2);
    //Serial.printf("pos 1: %d, pos 2: %d\n", pos1, pos2);
    
    delay(15);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  updateServo();
}
