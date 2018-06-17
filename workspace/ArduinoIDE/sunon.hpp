#include "arduino.h"


class Sunon{
private:
  int pwmPin;

public:

  Sunon();

  Sunon(int pwmPin);

  void Set(bool mode);


  
};

