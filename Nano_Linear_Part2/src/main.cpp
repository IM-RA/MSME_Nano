#include <Arduino.h>

#define motor1 5
#define motor2 6
#define pot A0

uint16_t pos_current = 0;
uint16_t pos_target = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pos_current = analogRead(pot);
  
  if(pos_current > pos_target){
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
  }
  else if(pos_current < pos_target){
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, HIGH);
  }
  else if(pos_target == pos_current){
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
  }

  Serial.println("Target:" + String(pos_target) + ",Lower:0,Higher:1024,Current:" + String(pos_current));
}