/*
 * L298N library to control engines using a L298N board.
 * José Manuel Molina Pacual, August 2017
 * Collado Villalba, Madrid, Spain
 * GNU 3.0 License
 */

#ifndef L298N_h
#define L298N_h_h

#include "Arduino.h"
//How the engines work
// To make the engine move FWD set pin 1/3 to low and 2/4 to high
// Then apply power with the value on PWM pin (0-255)
// To stop it just put 1/3 and 2/4 to low

class L298N
{
public:
	L298N();
	void setup(int leftEnginePWMPin,int rightEnginePWMPin,int leftEngineIn1Pin,int leftEngineIn2Pin,int rightEngineIn3Pin,int rightEngineIn4Pin);
	void leftEngineStop();
	void leftEngineSetSpeed(int speedE);
	void leftEngineFWD(int speedE);
	void leftEngineREV(int speedE);
	void rightEngineStop();
	void rightEngineSetSpeed(int speedE);
	void rightEngineFWD(int speedE);
	void rightEngineREV(int speedE);
	void turnLeft(int speedE);
	void turnLeft(int speedE, int divisor);
	void turnLeftREV(int speedE);
	void turnLeftREV(int speedE, float divisor);
	void rotateLeft(int speedE);
	void rotateLeft(int speedr, int speedl);
	void turnRight(int speedE);
	void turnRight(int speedE, int divisor);
	void turnRightREV(int speedE);
	void turnRightREV(int speedE, float divisor);
	void rotateRight(int speedE);
	void rotateRight(int speedl, int speedr);
	void goFWD(int speedE);
	void goREV(int speedE);
	void stop();


	void testEngines();
	void testRotation();
	void testFWD();
	void testREV();
	void testFWDREVROT();


private:
	int leftEnginePWMPin=11;
	int rightEnginePWMPin=10;
	int leftEngineIn1Pin=9;
	int leftEngineIn2Pin=8;
	int rightEngineIn3Pin=7;
	int rightEngineIn4Pin=6;
};

#endif
