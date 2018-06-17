#include "sunon.hpp"



class MotorController{
private:
  int motorPin;
  Sunon motor;

public:
  MotorController();
  
  MotorController(int motorPin);

  void Run();
  float GetDelayTime(){return delayTime;};
  void SetMotor(unsigned char motorDelay);
  
};

