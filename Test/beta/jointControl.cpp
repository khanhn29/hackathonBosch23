#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
#include "jointControl.h"

extern Adafruit_PWMServoDriver pwm;

void controlShoulderFR(int angle)
{
  if(angle > SAFE_ANGLE_SHOULDER_FR)
    angle = SAFE_ANGLE_SHOULDER_FR;
  if(angle < 0)
    angle = 0;
  pwm.setPWM(SERVO_NUM_SHOULDER_FR, 0, angleToPulse(angle));
}

void controlShoulderFL(int angle)
{
  if(angle > SAFE_ANGLE_SHOULDER_FL)
    angle = SAFE_ANGLE_SHOULDER_FL;
  if(angle < 0)
    angle = 0;
  pwm.setPWM(SERVO_NUM_SHOULDER_FL, 0, angleToPulse(angle));
}

void controlShoulderRR(int angle)
{
  if(angle > SAFE_ANGLE_SHOULDER_RR)
    angle = SAFE_ANGLE_SHOULDER_RR;
  if(angle < 0)
    angle = 0;
  pwm.setPWM(SERVO_NUM_SHOULDER_RR, 0, angleToPulse(angle));
}

void controlShoulderRL(int angle)
{
  if(angle > SAFE_ANGLE_SHOULDER_RL)
    angle = SAFE_ANGLE_SHOULDER_RL;
  if(angle < 0)
    angle = 0;
  pwm.setPWM(SERVO_NUM_SHOULDER_RL, 0, angleToPulse(angle));
}

void controlArmFR(int angle)
{
  if(angle > SAFE_MAX_ANGLE_ARM_FR)
    angle = SAFE_MAX_ANGLE_ARM_FR;
  if(angle < SAFE_MIN_ANGLE_ARM_FR)
    angle = SAFE_MIN_ANGLE_ARM_FR;
  pwm.setPWM(SERVO_NUM_ARM_FR, 0, angleToPulse(angle));
}

void controlArmRL(int angle)
{
  if(angle > SAFE_MAX_ANGLE_ARM_RL)
    angle = SAFE_MAX_ANGLE_ARM_RL;
  if(angle < SAFE_MIN_ANGLE_ARM_RL)
    angle = SAFE_MIN_ANGLE_ARM_RL;
  pwm.setPWM(SERVO_NUM_ARM_RL, 0, angleToPulse(angle));
}

void controlArmFL(int angle)
{
  if(angle > SAFE_MAX_ANGLE_ARM_FL)
    angle = SAFE_MAX_ANGLE_ARM_FL;
  if(angle < SAFE_MIN_ANGLE_ARM_FL)
    angle = SAFE_MIN_ANGLE_ARM_FL;
  pwm.setPWM(SERVO_NUM_ARM_FL, 0, angleToPulse(angle));
}

void controlArmRR(int angle)
{
  if(angle > SAFE_MAX_ANGLE_ARM_RR)
    angle = SAFE_MAX_ANGLE_ARM_RR;
  if(angle < SAFE_MIN_ANGLE_ARM_RR)
    angle = SAFE_MIN_ANGLE_ARM_RR;
  pwm.setPWM(SERVO_NUM_ARM_RR, 0, angleToPulse(angle));
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}