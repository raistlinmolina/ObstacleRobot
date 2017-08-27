#include "src/Sonar/Sonar.h"
#include "src/L298N/L298N.h"

Sonar sonar;
L298N l298n;


//The servo library disables PWM (analogWrite) on pins 9 and 10, so do not use them for motor PWM
long minimumSpace = 25;

void setup(){
  Serial.begin(9600);
  sonar.setup(2,12,13);
  //The servo library disables PWM (analogWrite) on pins 9 and 10, so do not use them for motor PWM
  l298n.setup(11,5,9,8,7,6);
}

void loop(){                          
  int slots=sonar.coverage/sonar.degreesStep;
  long distances[slots];
  boolean stopped = false;
  long freeSpace = sonar.getSonarRead();
  if (freeSpace <= minimumSpace){
    stopped = true;
    l298n.stop();
    sonar.sweep(&distances[0]);
    int bestDir = sonar.determineBestDirection(distances);
    //Turn to that direction, actually a bit difficult because motor speed depends on voltage :(
    //Well have to calculate it based on the degrees and try/error
    int multiplier = 1;
  
    if(bestDir <0){
      l298n.rotateLeft(100);                        
      int delayT = bestDir * -1 * multiplier;
      delay(delayT);
    }else if(bestDir >0){
       l298n.rotateRight(100);
      int delayT = bestDir * multiplier;
      delay(delayT);   
    }                                                                                                  
  }
  freeSpace = sonar.getSonarRead();
  if (stopped && freeSpace > minimumSpace){
    l298n.rightEngineFWD(200);
  }
 
  
  //Serial.println(slots);
  //Serial.println("Distances ");

  /*for (int i=0; i<slots;i++){
    Serial.println(total[i]);
  }*/

}


