
#include "hcsr04.hpp"
#include "motorController.hpp"

#define PWM_PIN     7
#define TRIGGER_PIN 9
#define ECHO_PIN    10


long duration;
int distance;
float movav=0;

Hcsr04 distSensor;
MotorController motor;


void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  distSensor = Hcsr04(TRIGGER_PIN, ECHO_PIN);
  motor = MotorController(PWM_PIN);

  Serial.begin(9600);
}

void loop() {

  long dist = distSensor.Get();
  movav=0.99*movav+0.01*dist;

  unsigned char nByteMotorspeed = 0;

  while (Serial.available())
  {
    nByteMotorspeed = Serial.read();
    motor.SetMotor(nByteMotorspeed);
  }
  

  int imovav = (int)movav;
  unsigned char byte1 = (unsigned char)imovav;

  Serial.write(byte1);


  motor.Run();
  
}
