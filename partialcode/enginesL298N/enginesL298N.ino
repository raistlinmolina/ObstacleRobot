int leftEnginePWMPin=11;
int rightEnginePWMPin=10;
int leftEngineIn1Pin=9;
int leftEngineIn2Pin=8;
int rightEngineIn3Pin=7;
int rightEngineIn4Pin=6;

//How the engines work
// To make the engine move FWD set pin 1/3 to low and 2/4 to high
// Then apply power with the value on PWM pin (0-255)
// To stop it just put 1/3 and 2/4 to low

void setupEngines(){
  pinMode(leftEnginePWMPin,OUTPUT);
  pinMode(rightEnginePWMPin,OUTPUT);
  pinMode(leftEngineIn1Pin,OUTPUT);
  pinMode(leftEngineIn2Pin,OUTPUT);
  pinMode(rightEngineIn3Pin,OUTPUT);
  pinMode(rightEngineIn4Pin,OUTPUT);
}

void leftEngineStop(){
  digitalWrite(leftEngineIn1Pin, LOW);
  digitalWrite(leftEngineIn2Pin, LOW);
  analogWrite(leftEnginePWMPin, 0);
}

void leftEngineSetSpeed(int speedE){
  analogWrite(leftEnginePWMPin, speedE); 
}

void leftEngineFWD(int speedE){
  digitalWrite(leftEngineIn1Pin, LOW);
  digitalWrite(leftEngineIn2Pin, HIGH);
  analogWrite(leftEnginePWMPin, speedE);
}

void leftEngineREV(int speedE){
  digitalWrite(leftEngineIn1Pin, HIGH);
  digitalWrite(leftEngineIn2Pin, LOW);
  analogWrite(leftEnginePWMPin, speedE);
}

void rightEngineStop(){
  digitalWrite(rightEngineIn3Pin, LOW);
  digitalWrite(rightEngineIn4Pin, LOW);
  analogWrite(rightEnginePWMPin, 0);
}

void rightEngineSetSpeed(int speedE){
  analogWrite(rightEnginePWMPin, speedE); 
}

void rightEngineFWD(int speedE){
  digitalWrite(rightEngineIn3Pin, LOW);
  digitalWrite(rightEngineIn4Pin, HIGH);
  analogWrite(rightEnginePWMPin, speedE);
}

void rightEngineREV(int speedE){
  digitalWrite(rightEngineIn3Pin, HIGH);
  digitalWrite(rightEngineIn4Pin, LOW);
  analogWrite(rightEnginePWMPin, speedE);
}

void turnLeft(int speedE){
  rightEngineFWD(speedE);
  leftEngineStop();
}

void turnLeft(int speedE, int divisor){
  rightEngineFWD(speedE);
  int speedL = speedE/divisor;
  leftEngineFWD(speedL);
}

void turnLeftREV(int speedE){
  leftEngineREV(speedE);
  rightEngineStop();
}

void turnLeftREV(int speedE, float divisor){
  leftEngineREV(speedE);
  int speedR = speedE/divisor;
  rightEngineREV(speedR);
}

void rotateLeft(int speedE){
  rightEngineFWD(speedE);
  leftEngineREV(speedE);
}

void rotateLeft(int speedr, int speedl){
  rightEngineFWD(speedr);
  leftEngineREV(speedl);
}

void turnRight(int speedE){
  leftEngineFWD(speedE);
  rightEngineStop();
}

void turnRight(int speedE, int divisor){
  leftEngineFWD(speedE);
  int speedR = speedE/divisor;
  rightEngineFWD(speedR);
}

void turnRightREV(int speedE){
  rightEngineREV(speedE);
  leftEngineStop();
}

void turnRightREV(int speedE, float divisor){
  rightEngineREV(speedE);
  int speedL=speedE/divisor;
  leftEngineREV(speedL);
}

void rotateRight(int speedE){
  leftEngineFWD(speedE);
  rightEngineREV(speedE);
}

void rotateRight(int speedl, int speedr){
  leftEngineFWD(speedl);
  rightEngineREV(speedr);
}

void goFWD(int speedE){
  rightEngineFWD(speedE);
  leftEngineFWD(speedE);
}

void goREV(int speedE){
  rightEngineREV(speedE);
  leftEngineREV(speedE);
}


void setup() {
  setupEngines();
}

void testEngines(){
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

void testRotation(){
  rotateLeft(254);
  delay(2000);
  rotateRight(254);
  delay(2000);
}

void testFWD(){
  goFWD(254);
  delay(2000);
}

void testREV(){
  goREV(254);
  delay(2000);
}

void testFWDREVROT(){
  testFWD();
  testREV();
  testRotation();
}

void loop() {
  rightEngineFWD(100);
}
