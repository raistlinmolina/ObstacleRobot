/*
 * Sonar.cpp - Library to control the usound sensor at the fron of the car.
 * José Manuel Molina Pacual, August 2017
 * Collado Villalba, Madrid, Spain
 * GNU 3.0 License
 */

#include "Arduino.h"
#include "Sonar.h"

Sonar::Sonar(){
}

void Sonar::setup(int servoPin, int uSoundSensorPinOut, int uSoundSensorPinIn){
  //Housekeeping
  /*  Serial.begin(9600);*/
  this->servoPin = servoPin;
  this->uSonicSensorPinOut = uSoundSensorPinOut;
  this->uSonicSensorPinIn = uSoundSensorPinIn;
  
  // attaches the servo on pin servoPin to the servo object
  myservo.attach(servoPin);  
  //Set the usoundSensor pins
  pinMode(uSoundSensorPinOut, OUTPUT); 
  pinMode(uSoundSensorPinIn, INPUT);
}



//This function performs a distance read
//times is the number of times we want the sensor to read the distance
//We stay on the safe side and return the lower distance read.

long Sonar::getSonarRead (){
  long distance[timesToRead];
  for (int i = 0; i<timesToRead; i++){
    digitalWrite(this->uSonicSensorPinOut,LOW); //We first stabilize the sensor
    delayMicroseconds(this->uSonicSensorDelay);
    digitalWrite(this->uSonicSensorPinOut, HIGH); // We send the usonic pulse
    delayMicroseconds(this->uSonicSensorReadDelay);
    digitalWrite(this->uSonicSensorPinOut, LOW);
    
    /*Function to read the time that has passed since we sent the pulse until we receive the echo*/
    long time=pulseIn(this->uSonicSensorPinIn, HIGH); 
    
    distance[i]= long(0.017*time);
    delay(100); 
  }
  
  long lowerDistance = 3000; //A safe value
  for (int i = 0; i<timesToRead; i++){
    if(distance[i] < lowerDistance){
		lowerDistance = distance[i];
	}
  }
  return lowerDistance;
}

boolean Sonar::thresholdPassed(){
  if (getSonarRead() < this->obstacleThreshold) return true; else return false;
}

int Sonar::determineBestDirection(long  distances[]) {
  //Here goes the algorithm to determine the best option;
  //Maybe it could be improved to return a list of ordered options from better to worse.
  //Result: -90 full left, 0 center, 90 full right.
  int currentBest = 0;
  int currentPos = 0;
  int slots=(coverage/degreesStep)+1;
  for (int i=0; i<slots; i++){
    if (currentBest < distances[i]){
      currentBest = distances[i];
      currentPos = i;
    }
  }
  currentPos = (currentPos * degreesStep) - centerPos;
  return currentPos;
}

void Sonar::sweep(long *distances) {
  //Do barrage and return distances read.  
  myservo.write(initialPos);
  delay(50);
  int slots = (coverage/degreesStep)+1;
  for (int pos = 0; pos <= coverage; pos += degreesStep) { 
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits for the servo to reach the position
    distances [pos/degreesStep] = getSonarRead();
    
  }
  myservo.write(servoStorePos);
  delay(300);
  return distances;
}
