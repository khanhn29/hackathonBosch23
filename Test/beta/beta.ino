#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
#include "jointControl.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60); 
  
  transformstoCar();
  delay(5000);
}
void loop() {
  String inputString = "ccccoddddoaaaafobbbbfoe";

  int stringLength = inputString.length(); // Get the length of the string

  for (int i = 0; i < stringLength; i++) {
    char currentChar = inputString.charAt(i);
    Serial.println(currentChar);
    parseAndCallFunction(currentChar);
  }

  while(1);
}

void moveBackward()
{
  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmFL(RAISE_ANGLE_ARM_FL);
  controlArmRR(RAISE_ANGLE_ARM_RR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  delay(260);
  controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  delay(260);
  controlArmFR(RAISE_ANGLE_ARM_FR);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  controlArmRL(RAISE_ANGLE_ARM_RL);
  delay(260);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
  delay(260);
}

void moveForward()
{
  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmFL(RAISE_ANGLE_ARM_FL);
  controlArmRR(RAISE_ANGLE_ARM_RR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  delay(260);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
  delay(265);
  controlArmFR(RAISE_ANGLE_ARM_FR);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  controlArmRL(RAISE_ANGLE_ARM_RL);
  delay(260);
  controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  delay(265);
}

void transformstoCar() //e
{
  controlShoulderFR(CLOSE_ANGLE_SHOULDER_FR);
  controlShoulderFL(CLOSE_ANGLE_SHOULDER_FL);
  controlShoulderRR(CLOSE_ANGLE_SHOULDER_RR);
  controlShoulderRL(CLOSE_ANGLE_SHOULDER_RL);

  controlArmFR(CLOSE_ANGLE_ARM_FR);
  controlArmRL(CLOSE_ANGLE_ARM_RL);
  controlArmFL(CLOSE_ANGLE_ARM_FL);
  controlArmRR(CLOSE_ANGLE_ARM_RR);
}

void transformstoSpider() //f
{
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);

  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
}

void rotateLeft()
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
void rotateRight()
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

void parseAndCallFunction(const char letter) {
  switch (letter) {
    case 'o':
      delay(1000);
      break;
    case 'a':
      moveForward();
      break;
    case 'b':
      moveBackward();
      break;
    case 'c':
      rotateRight();
      break;
    case 'd':
      rotateLeft();
      break;
    case 'e':
      transformstoCar();
      break;
    case 'f':
      transformstoSpider();
      break;
    default:
      Serial.println("Invalid input.");
      break;
  }
}
