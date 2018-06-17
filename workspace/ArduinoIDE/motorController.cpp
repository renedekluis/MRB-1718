#include "motorController.hpp"


MotorController::MotorController():
  motor(7)
{
  
}

MotorController::MotorController(int motorPin):
  motor(motorPin)
{
  
}

void MotorController::Run()
{
  motor.Set(0);
  delay(delayTime);
  motor.Set(1);
}


void MotorController::SetMotor(unsigned char motorDelay)
{
  delayTime = (int)motorDelay;
}

