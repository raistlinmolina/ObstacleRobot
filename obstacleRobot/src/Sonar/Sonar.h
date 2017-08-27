/*
 * Sonar.h - Library to control the usound sensor at the fron of the car.
 * José Manuel Molina Pacual, August 2017
 * Collado Villalba, Madrid, Spain
 * GNU 3.0 License
 */

#ifndef Sonar_h
#define Sonar_h

#include "Arduino.h"
#include "Servo.h"

class Sonar
{
  public:
    Sonar();
    void setup(int servoPin, int uSoundSensorPinOut, int uSoundSensorPinIn);
    long getSonarRead();
    int determineBestDirection(long  distances[]);
    void sweep(long *distances);
    boolean thresholdPassed();
    int degreesStep = 15; // Degress to advance in each step
    
    int coverage=180;
    
  private:
    
    //Servo variables
    Servo myservo;  // create servo object to control a servo
    // Up to twelve servo objects can be created on most boards
  
    int servoPos = 0;    // variable to store the servo position
    int servoPin = 2;
    int initialPos = 0; // Initial servo position (degrees)
    
    int servoStorePos = 90; //Position to put the servo while moving
    int centerPos = 90;
    
    
	//USound sensor variables
	int uSonicSensorPinOut = 12; // Pin to trigger the usound pulse
	int uSonicSensorPinIn = 13; // Pin to read (echo) the usound rebound time
	const int uSonicSensorDelay = 5; // Delay to let the sensor stabilize
	const int uSonicSensorReadDelay = 10; // Delay to allow the sent pulse to complete
	const float formula = 0.017; // Multiplier to pass sensor reading to cm
		/* Sound speed in cm/microsecond divide by two as the time it took the bounce 
			is double the time to travel the distance*/
	
	int obstacleThreshold = 25; //Under this distance the Sensor will raise an alarm
	int timesToRead = 3; // Times to read the distance to determine it.
	

};
 
#endif
