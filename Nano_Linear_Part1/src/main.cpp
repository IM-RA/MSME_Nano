#include <Arduino.h>

#define motor1 5
#define motor2 6
#define pot A0

uint8_t pos_current = 0;

double current_time = 0;
double past_time = 0;
double duration = 1500;

bool CW = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
 
  Serial.begin(9600);
}

void loop() {
  current_time = millis();
  pos_current = analogRead(pot);
  // put your main code here, to run repeatedly:

  //Serial.println(pos_current);
  
  if(current_time-past_time >= 1500){
    past_time = current_time;
    CW = !CW;
  }

  if(CW){
    Serial.println("Forward");
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
  }
  else{
    Serial.println("Backward");
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, HIGH);
  }
  
}