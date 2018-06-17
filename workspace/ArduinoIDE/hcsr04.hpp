
#include "arduino.h"



class Hcsr04{
private:
  int trig;
  int echo;


  long duration;
  int distance;

  int ConvTime2Dist(long time);

public:
  Hcsr04();
  Hcsr04(int trigger, int echo);

  int Get();
  
};

