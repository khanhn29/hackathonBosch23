#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60); 
  controlShoulderFR(CLOSE_ANGLE_SHOULDER_FR);
  controlShoulderFL(CLOSE_ANGLE_SHOULDER_FL);
  controlShoulderRR(CLOSE_ANGLE_SHOULDER_RR);
  controlShoulderRL(CLOSE_ANGLE_SHOULDER_RL);

  controlArmFR(CLOSE_ANGLE_ARM_FR);
  controlArmRL(CLOSE_ANGLE_ARM_RL);
  controlArmFL(CLOSE_ANGLE_ARM_FL);
}
void loop() {

  // for( int angle =0; angle<181; angle +=20)
  // {
  //   for(int num = 0; num<16;num++)
  //   {
  //   pwm.setPWM(num, 0, angleToPulse(angle) );
  //   }
  // }
  // delay(1000);
  // controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  // controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  // controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  // controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  // delay(2000);
  // controlShoulderFR(CLOSE_ANGLE_SHOULDER_FR);
  // controlShoulderFL(CLOSE_ANGLE_SHOULDER_FL);
  // controlShoulderRR(CLOSE_ANGLE_SHOULDER_RR);
  // controlShoulderRL(CLOSE_ANGLE_SHOULDER_RL);
  // delay(2000);
  // controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  // controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  // controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  // controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  // delay(2000);
  // controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
  // controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
  // controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
  // controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
  // delay(2000);

  // controlShoulderFL(MIDDLE_ANGLE_SHOULDER_FL);
  // controlShoulderFR(OPEN_ANGLE_SHOULDER_FR);
  // controlShoulderRL(MIDDLE_ANGLE_SHOULDER_RL);
  // controlShoulderRR(OPEN_ANGLE_SHOULDER_RR);
  // delay(1000);
  // controlShoulderFR(MIDDLE_ANGLE_SHOULDER_FR);
  // controlShoulderFL(OPEN_ANGLE_SHOULDER_FL);
  // controlShoulderRR(MIDDLE_ANGLE_SHOULDER_RR);
  // controlShoulderRL(OPEN_ANGLE_SHOULDER_RL);
  // delay(1000);
  // controlArmFR(CLOSE_ANGLE_ARM_FR);
  // controlArmRL(CLOSE_ANGLE_ARM_RL);
  // controlArmFL(CLOSE_ANGLE_ARM_FL);
  controlArmRR(CLOSE_ANGLE_ARM_RR);
  delay(2000);
  // controlArmFR(STAND_ANGLE_ARM_FR);
  // controlArmRL(STAND_ANGLE_ARM_RL);
  // controlArmFL(STAND_ANGLE_ARM_FL);
  controlArmRR(STAND_ANGLE_ARM_RR);
  delay(1000);
  // controlArmFR(RAISE_ANGLE_ARM_FR);
  // controlArmRL(RAISE_ANGLE_ARM_RL);
  // controlArmFL(RAISE_ANGLE_ARM_FL);
  controlArmRR(RAISE_ANGLE_ARM_RR);
  delay(1000);
}
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