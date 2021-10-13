#include <Arduino.h>

#define motor1 5
#define motor2 6
#define pot A0

uint16_t pos_current = 0;
uint16_t pos_target = 500;

int16_t error = 0;

void set_motor(){
  if(error > 0){
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
  }
  else if(error < 0){
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, HIGH);
  }
  else{
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
  }
}

void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pos_current = analogRead(pot);
  pos_target = analogRead(A2);
  
  error = pos_target - pos_current;

  set_motor();

  Serial.println(String(pos_target) + ",0,1024," + String(pos_current) );
}

