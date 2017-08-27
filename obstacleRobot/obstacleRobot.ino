#include "src/Sonar/Sonar.h"
#include "src/L298N/L298N.h"

Sonar sonar;
L298N l298n;

long minimumSpace = 15;

void setup(){
  //Serial.begin(9600);
  sonar.setup(2,12,13);
  l298n.setup(11,10,9,8,7,6);
}

void loop(){                          
  int slots=sonar.coverage/sonar.degreesStep;
  long distances[slots];
  long freeSpace = sonar.getSonarRead();
  if (freeSpace <= minimumSpace){
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
       l298n.rotateLeft(100);
      int delayT = bestDir * -1 * multiplier;
      delay(delayT);   
    }                                                                                                  
  }
  freeSpace = sonar.getSonarRead();
  if (freeSpace > minimumSpace){
    l298n.goFWD(100);
  }
 
  
  //Serial.println(slots);
  //Serial.println("Distances ");

  /*for (int i=0; i<slots;i++){
    Serial.println(total[i]);
  }*/

}


