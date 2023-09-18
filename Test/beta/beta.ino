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
  String inputString = "ccc";
  parseAndCallFunction(inputString);
}

void moveBackward()
{
  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmFL(RAISE_ANGLE_ARM_FL);
  controlArmRR(RAISE_ANGLE_ARM_RR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  delay(1000);
  controlArmFR(RAISE_ANGLE_ARM_FR);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  controlArmRL(RAISE_ANGLE_ARM_RL);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
  delay(1000);
}

void moveForward()
{
  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmFL(RAISE_ANGLE_ARM_FL);
  controlArmRR(RAISE_ANGLE_ARM_RR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
  delay(1000);
  controlArmFR(RAISE_ANGLE_ARM_FR);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  controlArmRL(RAISE_ANGLE_ARM_RL);
  controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  delay(1000);
}

void transformstoCar()
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

void transformstoSpider()
{
  controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
  controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
  controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
  controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);

  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
}

void rotateRight()
{
  controlArmFR(RAISE_ANGLE_ARM_FR);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  controlArmRL(RAISE_ANGLE_ARM_RL);
  controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
  delay(800);
  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmFL(RAISE_ANGLE_ARM_FL);
  controlArmRR(RAISE_ANGLE_ARM_RR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  delay(801);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  delay(802);

  controlArmFR(STAND_ANGLE_ARM_FR);
  controlArmFL(RAISE_ANGLE_ARM_FL);
  controlArmRR(RAISE_ANGLE_ARM_RR);
  controlArmRL(STAND_ANGLE_ARM_RL);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(CLOSE_ANGLE_SHOULDER_FL);
  controlShoulderRR(CLOSE_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  delay(800);
  controlArmFR(RAISE_ANGLE_ARM_FR);
  controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  controlArmRL(RAISE_ANGLE_ARM_RL);
  delay(801);
  controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  delay(802);
}

void parseAndCallFunction(const String &inputString) {
  char letter = inputString.charAt(0); // Get the first character of the input string

  switch (letter) {
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
      // rotateLeft();
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
