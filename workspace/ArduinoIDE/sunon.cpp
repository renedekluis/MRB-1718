#include "sunon.hpp"



Sunon::Sunon():
  pwmPin(7)
{
  pinMode(pwmPin, OUTPUT);
}

Sunon::Sunon(int pwmPin):
  pwmPin(pwmPin)
{
  pinMode(pwmPin, OUTPUT);
}

void Sunon::Set(bool mode)
{
  digitalWrite(pwmPin, mode);
}

