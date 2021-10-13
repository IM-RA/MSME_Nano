#include <Arduino.h>

#define motor1 5
#define motor2 6
#define pot A0

uint16_t pos_current = 0;
uint16_t pos_target = 100;

int16_t error = 0;
int16_t control = 0;
int16_t kP = 5;

uint8_t speed=255;

void set_motor(){

  uint16_t u_control = abs(control);

  if(u_control < 130){
    speed = 0;
  }
  else if(u_control > 255){
    speed = 255;
  }
  else{
    speed = u_control;
  }

  if(control > 0){
    analogWrite(motor1, speed);
    digitalWrite(motor2, LOW);
  }
  else if(control < 0){
    digitalWrite(motor1, LOW);
    analogWrite(motor2, speed);
  }
  else{
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
  }
}

void pid(){
  control = kP * error;
}

void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pos_target =analogRead(A2);
  pos_current = analogRead(pot);

  error = pos_target - pos_current;  
  pid();
  set_motor();
  
  Serial.println("Target:" + String(pos_target) + ",Min:0,Max:1024,POS:" + String(pos_current) + ",Speed:" + String(speed));
}

