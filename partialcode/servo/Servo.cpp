/*
 * Sonar.h - Library to control the usound sensor at the fron of the car.
 * José Manuel Molina Pacual, August 2017
 * Collado Villalba, Madrid, Spain
 * GNU 3.0 License
 */

#include "Arduino.h"
#include "Sonar.h"

Sonar::Sonar(int pin){
  myservo.attach(servoPin);  // attaches the servo on pin servoPin to the servo object
}

int Sonar::getSonarRead(){
  //Here goes the code to get the uSound read
  return 100;
}

int Sonar::determineBestDirection(int  distances[]) {
  //Here goes the algorithm to determine the best option;
  //Maybe it could be improved to return a list of ordered options from better to worse.
  //Result: -90 full left, 0 center, 90 full right.
  int currentBest = 0;
  int currentPos = 0;
  for (int i=0; i<sizeof(distances); i++){
    if (currentBest < distances[i]){
      currentBest = distances[i];
      currentPos = i;
    }
  }
  currentPos = (currentPos * degressStep) - centerPos;
  return currentPos;
}

int* Sonar::sweep() {
  //Do barrage and return distances read.  
  myservo.write(initialPos);
  delay(500);
  int slots = 180/degressStep;
  int distances [slots];
  delay(15);
  int betterDirection = initialPos;
  for (int pos = 0; pos <= 180; pos += degressStep) { 
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    distances [pos/degressStep] = getSonarRead();
    delay(500);                       // waits 15ms for the servo to reach the position
  }
  myservo.write(90);
  delay(3000);
  return distances;
}
