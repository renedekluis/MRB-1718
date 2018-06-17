#include "sunon.hpp"



class MotorController{
private:
  int motorPin;
  Sunon motor;
  float delayTime = 17.80;
  float midDelay = 17.80;
  float oldDist =17.80;

public:
  MotorController();
  
  MotorController(int motorPin);

  void Run();
  float GetDelayTime(){return delayTime;};
  void SetMotor(unsigned char motorDelay);
  
};

