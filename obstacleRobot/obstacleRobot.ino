#include <Servo.h>

long distance;
long time;
//const int ledPin = 6 ;
const int usonicSensorPinOut = 12; // Pin to trigger the usound pulse
const int usonicSensorPinIn = 13; // Pin to read (echo) the usound rebound time
const int usonicSensorDelay = 5; // Delay to let the sensor stabilize
const int usonicSensorReadDelay = 10; // Delay to allow the sent pulse to complete
const float formula = 0.017; // Multiplier to pass sensor reading to cm
/* Sound speed in cm/microsecond divide by two as the time it took the bounce 
is double the time to travel the distance*/
const long obstacleThreshold = 100; //If we read less than this cm we assume there is a car parked under.
const int timesToRead = 1; // Times to read the distance to determine it.


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int servoPos = 0;    // variable to store the servo position
int servoPin = 2;
int initialPos = 0; // Initial servo position (degrees)
int degressStep = 15; // Degress to advance in each step
int servoStorePos = 90; //Position to put the servo while moving

void uSoundSensorSetup(){
  Serial.begin(9600);
  pinMode(usonicSensorPinOut, OUTPUT); 
  pinMode(usonicSensorPinIn, INPUT);
  //pinMode( ledPin , OUTPUT) ; 
}

void servoSetup(){
  myservo.attach(servoPin);  // attaches the servo on pin servoPin to the servo object
}

long readDistance (int times){
  long distance[times];
  for (int i = 0; i<times; i++){
    digitalWrite(usonicSensorPinOut,LOW); //We first stabilize the sensor
    delayMicroseconds(5);
    digitalWrite(usonicSensorPinOut, HIGH); // We send the usonic pulse
    delayMicroseconds(10);
    digitalWrite(usonicSensorPinOut, LOW);
    
    /*Function to read the time that has passed since we sent the pulse until we receive the echo*/
    time=pulseIn(usonicSensorPinIn, HIGH); 
    
    distance[i]= int(0.017*time);
    delay(100); 
  }
  
  long total = 0;
  for (int i = 0; i<times; i++){
    total = total + distance[i];
  }
  total = total / times;
  
  /*Monitorización en centímetros por el monitor serial*/
  Serial.println("Distance ");
  Serial.println(total);
  Serial.println(" cm.");
  delay(100);
  return total;
}

boolean thresholdPassed(){
  if (readDistance(timesToRead) < obstacleThreshold) return true; else return false;
}

int avoidObstacle(){
  Serial.println("Obstacle detected, initiating avoidance maneouvers.");
}

int checkObstacles(){
  boolean obstacleFound = thresholdPassed();
  if (obstacleFound){
    avoidObstacle();
    //digitalWrite( ledPin , HIGH);
  }else{
    //digitalWrite( ledPin , LOW);
  }
}

int getSonarRead(){
  //Here goes the code to get the uSound read
  return readDistance(timesToRead);
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

void setup(){
  uSoundSensorSetup();
  servoSetup();
}

void loop(){
  checkObstacles();
  }


