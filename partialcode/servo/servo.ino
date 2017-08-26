/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int servoPos = 0;    // variable to store the servo position
int servoPin = 2;
int initialPos = 0; // Initial servo position (degrees)
int degressStep = 15; // Degress to advance in each step
int servoStorePos = 90; //Position to put the servo while moving

void setup() {
  myservo.attach(servoPin);  // attaches the servo on pin servoPin to the servo object
}

int getSonarRead(){
  //Here goes the code to get the uSound read
  return 100;
}

int determineBestOption(int  distances[]) {
  //Here goes the algorithm to determine the best option;
  //Maybe it could be imporved to return a list of ordered options from better to worse.
  return 6;
}

int doBarrage() {
  //Do barrage and return direction in degrees of clearer path.  
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
  int bestDirection = 0;
  for (int slot = 0; slot <= slots; slot++) {
    bestDirection = determineBestOption(distances);
  }
  myservo.write(90);
  delay(3000);
  return bestDirection * degressStep;

}

void loop() {
  doBarrage();

}
