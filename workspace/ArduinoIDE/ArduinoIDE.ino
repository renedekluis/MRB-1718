
#include "hcsr04.hpp"
#include "motorController.hpp"

#define PWM_PIN     7
#define TRIGGER_PIN 9
#define ECHO_PIN    10
#define BUTTON1     44
#define BUTTON2     48

long duration;
int distance;
float movav=0;

Hcsr04 distSensor;
MotorController motor;
int butState1 = 0;
int butState2 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  distSensor = Hcsr04(TRIGGER_PIN, ECHO_PIN);
  motor = MotorController(PWM_PIN);


  
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);

  Serial.begin(9600);
}

void loop() {

  butState1 = digitalRead(BUTTON1);
  butState2 = digitalRead(BUTTON2);



  long dist = distSensor.Get();
  movav=0.99*movav+0.01*dist;

  unsigned char nByteMotorspeed = 0;

  while (Serial.available())
  {
    nByteMotorspeed = Serial.read();
    motor.SetMotor(nByteMotorspeed);
  }
  

  //unsigned char byte1 = dist & 0xff;
  //unsigned char byte2 = (dist >> (8*1)) & 0xff;
  unsigned char nul = 0;
  int imovav = (int)movav;
  unsigned char byte1 = (unsigned char)imovav;
/*
  Serial.print("dist");
  Serial.print(" ");
  Serial.print(movav);
  Serial.print(" ");
  Serial.print((int)byte1);
  Serial.print(" ");
  Serial.println((int)byte2);
*/
  
  //Serial.write(nul);
  //Serial.write(nul);
  //Serial.write(nul);
  //Serial.write(byte2);
  Serial.write(byte1);
  //Serial.write((byte1);
  /*
  Serial.print("Distance: ");
  if(dist < 100 && dist >= 10)
  {
    Serial.print(0);
  }
  if(dist < 10)
  {
    Serial.print(0);
    Serial.print(0);
  }
  Serial.println(dist);
*/
  
 
  
  

  motor.Run();

  


  

  
}
