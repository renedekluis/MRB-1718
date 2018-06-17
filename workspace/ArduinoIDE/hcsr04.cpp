
#include "hcsr04.hpp"


int Hcsr04::ConvTime2Dist(long time)
{
  return time*0.034/2;
}



Hcsr04::Hcsr04():
  trig(9),
  echo(10)
{
  
}

Hcsr04::Hcsr04(int trigger, int echo):
  trig(trigger),
  echo(echo)
{
  
}

int Hcsr04::Get()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = ConvTime2Dist(duration);
  
  return distance;
}

