#include <Arduino.h>
#include "config.h"
#include "motorControl.h"

void motor_FORWARD(int speed) {
	speed = constrain(speed, MIN_SPEED, MAX_SPEED);
	//FR
	digitalWrite(MOTOR_FR_IN1, LOW);
	analogWrite(MOTOR_FR_IN2, speed);
	//RR
	digitalWrite(MOTOR_RR_IN3, HIGH);
	analogWrite(MOTOR_RR_IN4, 255 - speed);
	//RL
	digitalWrite(MOTOR_RL_IN1, HIGH);
	analogWrite(MOTOR_RL_IN2, 255 - speed);
	//FL
	digitalWrite(MOTOR_FL_IN3, LOW);
	analogWrite(MOTOR_FL_IN4, speed);
	delay(1000);
	digitalWrite(MOTOR_FR_IN1, HIGH);
	digitalWrite(MOTOR_FR_IN2, HIGH);
	digitalWrite(MOTOR_RR_IN3, LOW);
	digitalWrite(MOTOR_RR_IN4, LOW);
	digitalWrite(MOTOR_RL_IN1, LOW);
	digitalWrite(MOTOR_RL_IN2, LOW);
	digitalWrite(MOTOR_FL_IN3, HIGH);
	digitalWrite(MOTOR_FL_IN4, HIGH);
}

void motor_BACKWARD(int speed) {
	speed = constrain(speed, MIN_SPEED, MAX_SPEED);
	//FR
	digitalWrite(MOTOR_FR_IN1, HIGH);
	analogWrite(MOTOR_FR_IN2, 255 - speed);
	//RR
	digitalWrite(MOTOR_RR_IN3, LOW);
	analogWrite(MOTOR_RR_IN4, speed);
	//RL
	digitalWrite(MOTOR_RL_IN1, LOW);
	analogWrite(MOTOR_RL_IN2, speed);
	//FL
	digitalWrite(MOTOR_FL_IN3, HIGH);
	analogWrite(MOTOR_FL_IN4, 255 - speed);
	delay(1000);
	digitalWrite(MOTOR_FR_IN1, LOW);
	digitalWrite(MOTOR_FR_IN2, LOW);
	digitalWrite(MOTOR_RR_IN3, HIGH);
	digitalWrite(MOTOR_RR_IN4, HIGH);
	digitalWrite(MOTOR_RL_IN1, HIGH);
	digitalWrite(MOTOR_RL_IN2, HIGH);
	digitalWrite(MOTOR_FL_IN3, LOW);
	digitalWrite(MOTOR_FL_IN4, LOW);
}
