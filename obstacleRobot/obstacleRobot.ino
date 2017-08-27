#include "src/Sonar/Sonar.h"
Sonar sonar;
void setup(){
  Serial.begin(9600);
  sonar.setup(2,12,13);
}

void loop(){
  int slots=sonar.coverage/sonar.degreesStep;
  long total[slots];
  
  sonar.sweep(&total[0]);
  delay(1000);
  Serial.println(slots);
  Serial.println("Distances ");

  for (int i=0; i<slots;i++){
    Serial.println(total[i]);
  }

}


