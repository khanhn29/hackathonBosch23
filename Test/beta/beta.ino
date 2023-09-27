#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
#include "jointControl.h"
#include "motorControl.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define CAR 0
#define SPIDER 1

int g_currentForm = CAR;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60);

  //Setup pin motor
  pinMode(MOTOR_FR_IN1, OUTPUT);
	pinMode(MOTOR_FR_IN2, OUTPUT);
	pinMode(MOTOR_RR_IN3, OUTPUT);
	pinMode(MOTOR_RR_IN4, OUTPUT);
	pinMode(MOTOR_FL_IN3, OUTPUT);
	pinMode(MOTOR_FL_IN4, OUTPUT);
	pinMode(MOTOR_RL_IN1, OUTPUT);
	pinMode(MOTOR_RL_IN2, OUTPUT);
  
  transformstoCar();
  delay(5000);
}
void loop() {
  String inputString = "wwweowwwweodddossseoqwwwo";

  int stringLength = inputString.length(); // Get the length of the string
  inputString.toLowerCase();
  for (int i = 0; i < stringLength; i++) {
    char currentChar = inputString.charAt(i);
    Serial.println(currentChar);
    parseAndCallFunction(currentChar);
  }

  while(1);
}

void parseAndCallFunction(const char letter) {
  switch (letter) {
    case 'o':
      delay(1000);
      break;
    case 'w':
      moveForward();
      break;
    case 's':
      moveBackward();
      break;
    case 'd':
      rotateRight();
      break;
    case 'a':
      rotateLeft();
      break;
    case 'q':
      transformstoCar();
      break;
    case 'e':
      transformstoSpider();
      break;
    case 't':
      test();
    default:
      Serial.println("Invalid input.");
      break;
  }
}

void moveBackward()
{
  if(g_currentForm == SPIDER)
  {
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(RAISE_ANGLE_ARM_FL);
    controlArmRR(RAISE_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    delay(500);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(300);
    controlArmFR(RAISE_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(RAISE_ANGLE_ARM_RL);
    delay(500);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(300);
  }
  else
  {
    motor_BACKWARD(255);
  }
}

void moveForward()
{
  if(g_currentForm == SPIDER)
  {
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(RAISE_ANGLE_ARM_FL);
    controlArmRR(RAISE_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    delay(500);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(300);
    controlArmFR(RAISE_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(RAISE_ANGLE_ARM_RL);
    delay(500);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(300);
  }
  else
  {
    motor_FORWARD(255);
  }
}

void transformstoCar() //e
{
  controlShoulderFR(CLOSE_ANGLE_SHOULDER_FR);
  controlShoulderFL(CLOSE_ANGLE_SHOULDER_FL);
  controlShoulderRR(CLOSE_ANGLE_SHOULDER_RR);
  controlShoulderRL(CLOSE_ANGLE_SHOULDER_RL);
  delay(200);
  controlArmFR(CLOSE_ANGLE_ARM_FR);
  controlArmRL(CLOSE_ANGLE_ARM_RL);
  controlArmFL(CLOSE_ANGLE_ARM_FL);
  controlArmRR(CLOSE_ANGLE_ARM_RR);
  g_currentForm = CAR;
}

void transformstoSpider() //f
{
  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  // delay(400);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  g_currentForm = SPIDER;
}

void rotateLeft()
{
  if(g_currentForm == SPIDER)
  {
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(RAISE_ANGLE_ARM_FL);
    controlArmRR(RAISE_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    delay(265);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(RAISE_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(RAISE_ANGLE_ARM_RL);
    delay(265);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(260);
    transformstoSpider();
  }
  else
  {
    
  }
}
void rotateRight()
{
  if(g_currentForm == SPIDER)
  {
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(RAISE_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(RAISE_ANGLE_ARM_RL);
    delay(265);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(STAND_ANGLE_ARM_FL);
    controlArmRR(STAND_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
    controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
    controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
    controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
    delay(260);
    controlArmFR(STAND_ANGLE_ARM_FR);
    controlArmFL(RAISE_ANGLE_ARM_FL);
    controlArmRR(RAISE_ANGLE_ARM_RR);
    controlArmRL(STAND_ANGLE_ARM_RL);
    delay(265);
    controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
    controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
    controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
    controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
    delay(260);
    transformstoSpider();
  }
  else
  {

  }
}

void test()
{
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  controlArmFR(CLOSE_ANGLE_ARM_FR);
  controlArmRL(CLOSE_ANGLE_ARM_RL);
  controlArmFL(CLOSE_ANGLE_ARM_FL);
  controlArmRR(CLOSE_ANGLE_ARM_RR);
}
