#include <ESP32Servo.h>

#define SERVO_NUMBER 6
#define SERVO_LEFT_THIGH 13
#define SERVO_LEFT_KNEE 27
#define SERVO_LEFT_ANKLE 33
#define SERVO_RIGHT_THIGH 15
#define SERVO_RIGHT_KNEE 16
#define SERVO_RIGHT_ANKLE 18
#define SERVO_INITIAL_POS 0
#define SERVO_MAX_POS 15

Servo ServoObjects[SERVO_NUMBER];
int InitialServoPosition[SERVO_NUMBER];

int pos = 0;    // variable to store the servo position

Servo myServo;

void setupServos()
{
  // set pin pwm
  ServoObjects[0].attach(SERVO_LEFT_THIGH);
  ServoObjects[1].attach(SERVO_LEFT_KNEE);
  ServoObjects[2].attach(SERVO_LEFT_ANKLE);
  ServoObjects[3].attach(SERVO_RIGHT_THIGH);
  ServoObjects[4].attach(SERVO_RIGHT_KNEE);
  ServoObjects[5].attach(SERVO_RIGHT_ANKLE);
  myServo.attach(SERVO_LEFT_THIGH);

  // set initial pos of servo
  // for (int index = 0; index < SERVO_NUMBER; index++){
  //   ServoObjects[index].write(SERVO_INITIAL_POS);
  // }
  for (int index = 0; index < SERVO_NUMBER; index++){
    InitialServoPosition[index] = ServoObjects[index].read();
    Serial.printf("Servo %d = %d,\n", index, InitialServoPosition[index]);
  }
}

void readServos()
{
  Serial.println("Read servo position:");
  for (int index = 0; index < SERVO_NUMBER; index++){
    InitialServoPosition[index] = ServoObjects[index].read();
    Serial.printf("Servo %d = %d\n", index, myServo.read());
  }
}

void updateServos()
{
  for (pos = 0; pos <= SERVO_MAX_POS; pos += 1) {
    for (int index = 0; index <= SERVO_NUMBER; index += 1)
    {
      pos += InitialServoPosition[index];
      if (pos < 0 || pos > 180)
        continue;
      else 
        ServoObjects[index].write(pos);
    }
    delay(30);
  }
  for (pos = SERVO_MAX_POS; pos > 0; pos -= 1) {
    for (int index = 0; index <= SERVO_NUMBER; index += 1)
    {
      pos += InitialServoPosition[index];
      if (pos < 0 || pos > 180)
        continue;
      else 
        ServoObjects[index].write(pos);
    }
    delay(30);
  }
}

void setup() {
  Serial.begin(115200);
  setupServos();
}

void loop() {
  readServos();
  delay(2000);
  //updateServos();
}
