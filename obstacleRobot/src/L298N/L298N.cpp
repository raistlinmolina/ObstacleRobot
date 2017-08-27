//How the engines work
// To make the engine move FWD set pin 1/3 to low and 2/4 to high
// Then apply power with the value on PWM pin (0-255)
// To stop it just put 1/3 and 2/4 to low

#include "Arduino.h"
#include "L298N.h"

L298N::L298N(){
}

void L298N::setup(int leftEnginePWMPin,int rightEnginePWMPin,int leftEngineIn1Pin,int leftEngineIn2Pin,int rightEngineIn3Pin,int rightEngineIn4Pin){
  this->leftEnginePWMPin = leftEnginePWMPin;
  this->rightEnginePWMPin = rightEnginePWMPin;
  this->leftEngineIn1Pin = leftEngineIn1Pin;
  this->leftEngineIn2Pin = leftEngineIn2Pin;
  this->rightEngineIn3Pin = rightEngineIn3Pin;
  this->rightEngineIn4Pin = rightEngineIn4Pin;
  
  pinMode(leftEnginePWMPin,OUTPUT);
  pinMode(rightEnginePWMPin,OUTPUT);
  pinMode(leftEngineIn1Pin,OUTPUT);
  pinMode(leftEngineIn2Pin,OUTPUT);
  pinMode(rightEngineIn3Pin,OUTPUT);
  pinMode(rightEngineIn4Pin,OUTPUT);
}

void L298N::leftEngineStop(){
  digitalWrite(leftEngineIn1Pin, LOW);
  digitalWrite(leftEngineIn2Pin, LOW);
  analogWrite(leftEnginePWMPin, 0);
}

void L298N::leftEngineSetSpeed(int speedE){
  analogWrite(leftEnginePWMPin, speedE); 
}

void L298N::leftEngineFWD(int speedE){
  digitalWrite(leftEngineIn1Pin, LOW);
  digitalWrite(leftEngineIn2Pin, HIGH);
  analogWrite(leftEnginePWMPin, speedE);
}

void L298N::leftEngineREV(int speedE){
  digitalWrite(leftEngineIn1Pin, HIGH);
  digitalWrite(leftEngineIn2Pin, LOW);
  analogWrite(leftEnginePWMPin, speedE);
}

void L298N::rightEngineStop(){
  digitalWrite(rightEngineIn3Pin, LOW);
  digitalWrite(rightEngineIn4Pin, LOW);
  analogWrite(rightEnginePWMPin, 0);
}

void L298N::rightEngineSetSpeed(int speedE){
  analogWrite(rightEnginePWMPin, speedE); 
}

void L298N::rightEngineFWD(int speedE){
  digitalWrite(rightEngineIn3Pin, LOW);
  digitalWrite(rightEngineIn4Pin, HIGH);
  analogWrite(rightEnginePWMPin, speedE);
}

void L298N::rightEngineREV(int speedE){
  digitalWrite(rightEngineIn3Pin, HIGH);
  digitalWrite(rightEngineIn4Pin, LOW);
  analogWrite(rightEnginePWMPin, speedE);
}

void L298N::turnLeft(int speedE){
  rightEngineFWD(speedE);
  leftEngineStop();
}

void L298N::turnLeft(int speedE, int divisor){
  rightEngineFWD(speedE);
  int speedL = speedE/divisor;
  leftEngineFWD(speedL);
}

void L298N::turnLeftREV(int speedE){
  leftEngineREV(speedE);
  rightEngineStop();
}

void L298N::turnLeftREV(int speedE, float divisor){
  leftEngineREV(speedE);
  int speedR = speedE/divisor;
  rightEngineREV(speedR);
}

void L298N::rotateLeft(int speedE){
  rightEngineFWD(speedE);
  leftEngineREV(speedE);
}

void L298N::rotateLeft(int speedr, int speedl){
  rightEngineFWD(speedr);
  leftEngineREV(speedl);
}

void L298N::turnRight(int speedE){
  leftEngineFWD(speedE);
  rightEngineStop();
}

void L298N::turnRight(int speedE, int divisor){
  leftEngineFWD(speedE);
  int speedR = speedE/divisor;
  rightEngineFWD(speedR);
}

void L298N::turnRightREV(int speedE){
  rightEngineREV(speedE);
  leftEngineStop();
}

void L298N::turnRightREV(int speedE, float divisor){
  rightEngineREV(speedE);
  int speedL=speedE/divisor;
  leftEngineREV(speedL);
}

void L298N::rotateRight(int speedE){
  leftEngineFWD(speedE);
  rightEngineREV(speedE);
}

void L298N::rotateRight(int speedl, int speedr){
  leftEngineFWD(speedl);
  rightEngineREV(speedr);
}

void L298N::goFWD(int speedE){
  rightEngineFWD(speedE);
  leftEngineFWD(speedE);
}

void L298N::goREV(int speedE){
  rightEngineREV(speedE);
  leftEngineREV(speedE);
}

void L298N::stop(){
	leftEngineStop();
	rightEngineStop();
}


void L298N::testEngines(){
  //Test left engine, first rotate it counterclockwise (move FWD) from 0 to full speed
  leftEngineFWD(0);
  for (int i=0; i<255; i++){
    leftEngineSetSpeed(i);
  }
  delay(10000);
  //Then stop
  leftEngineStop();
  delay(2000);
  //And finally rotate it clockwise (move REV) 0 to full speed.
  leftEngineREV(0);
  for (int i=0; i<255; i++){
    leftEngineSetSpeed(i);
  }
  delay(10000);
  leftEngineStop();

  //Test right engine, first rotate it counterclockwise (move FWD) from 0 to full speed
  rightEngineFWD(0);
  for (int i=0; i<255; i++){
    rightEngineSetSpeed(i);
  }
  delay(10000);
  //Then stop
  rightEngineStop();
  delay(2000);
  //And finally rotate it clockwise (move REV) 0 to full speed.
  rightEngineREV(0);
  for (int i=0; i<255; i++){
    rightEngineSetSpeed(i);
  }
  delay(10000);
  rightEngineStop();
  
}

void L298N::testRotation(){
  rotateLeft(254);
  delay(2000);
  rotateRight(254);
  delay(2000);
}

void L298N::testFWD(){
  goFWD(254);
  delay(2000);
}

void L298N::testREV(){
  goREV(254);
  delay(2000);
}

void L298N::testFWDREVROT(){
  testFWD();
  testREV();
  testRotation();
}
