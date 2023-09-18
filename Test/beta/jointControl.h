#ifndef JOINTCONTROL_H
#define JOINTCONTROL_H
void controlShoulderFR(int angle);
void controlShoulderFL(int angle);
void controlShoulderRR(int angle);
void controlShoulderRL(int angle);
void controlArmFR(int angle);
void controlArmRL(int angle);
void controlArmFL(int angle);
void controlArmRR(int angle);
int angleToPulse(int ang);
#endif