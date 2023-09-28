#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
#include "jointControl.h"

extern Adafruit_PWMServoDriver pwm;

void controlShoulderFR(int angle)
{
  angle = constrain(angle, MIN_SAFE_ANGLE_SHOULDER_FR, MAX_SAFE_ANGLE_SHOULDER_FR);
  pwm.setPWM(SERVO_NUM_SHOULDER_FR, 0, angleToPulse(angle));
}

void controlShoulderFL(int angle)
{
  angle = constrain(angle, MIN_SAFE_ANGLE_SHOULDER_FL, MAX_SAFE_ANGLE_SHOULDER_FL);
  pwm.setPWM(SERVO_NUM_SHOULDER_FL, 0, angleToPulse(angle));
}

void controlShoulderRR(int angle)
{
  angle = constrain(angle, MIN_SAFE_ANGLE_SHOULDER_RR, MAX_SAFE_ANGLE_SHOULDER_RR);
  pwm.setPWM(SERVO_NUM_SHOULDER_RR, 0, angleToPulse(angle));
}

void controlShoulderRL(int angle)
{
  angle = constrain(angle, MIN_SAFE_ANGLE_SHOULDER_RL, MAX_SAFE_ANGLE_SHOULDER_RL);
  pwm.setPWM(SERVO_NUM_SHOULDER_RL, 0, angleToPulse(angle));
}

void controlArmFR(int angle)
{
  angle = constrain(angle, SAFE_MIN_ANGLE_ARM_FR, SAFE_MAX_ANGLE_ARM_FR);
  pwm.setPWM(SERVO_NUM_ARM_FR, 0, angleToPulse(angle));
}

void controlArmRL(int angle)
{
  angle = constrain(angle, SAFE_MIN_ANGLE_ARM_RL, SAFE_MAX_ANGLE_ARM_RL);
  pwm.setPWM(SERVO_NUM_ARM_RL, 0, angleToPulse(angle));
}

void controlArmFL(int angle)
{
  angle = constrain(angle, SAFE_MIN_ANGLE_ARM_FL, SAFE_MAX_ANGLE_ARM_FL);
  pwm.setPWM(SERVO_NUM_ARM_FL, 0, angleToPulse(angle));
}

void controlArmRR(int angle)
{
  angle = constrain(angle, SAFE_MIN_ANGLE_ARM_RR, SAFE_MAX_ANGLE_ARM_RR);
  pwm.setPWM(SERVO_NUM_ARM_RR, 0, angleToPulse(angle));
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
  //  Serial.print("Angle: ");Serial.print(ang);
  //  Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}