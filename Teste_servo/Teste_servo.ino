#include <Servo.h>

Servo gate;

void setup() {
  // put your setup code here, to run once:
  gate.attach(3);
  gate.write(90);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    gate.write(Serial.parseInt());
  }
}
