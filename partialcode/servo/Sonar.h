/*
 * Sonar.h - Library to control the usound sensor at the fron of the car.
 * José Manuel Molina Pacual, August 2017
 * Collado Villalba, Madrid, Spain
 * GNU 3.0 License
 */

#ifndef Sonar_h
#define Sonar_h

#include "Arduino.h"

class Sonar
{
  public:
    Sonar(int pin);
    int getSonarRead();
    int determineBestDirection(int  distances[]);
    int* sweep();
  private:
    Servo myservo;  // create servo object to control a servo
    // Up to twelve servo objects can be created on most boards
  
    int servoPos = 0;    // variable to store the servo position
    int servoPin = 2;
    int initialPos = 0; // Initial servo position (degrees)
    int degressStep = 15; // Degress to advance in each step
    int servoStorePos = 90; //Position to put the servo while moving
    int centerPos = 90;  
}
 
#endif
