#include <Arduino.h>

#define motor1 5
#define motor2 6
#define pot A0

uint16_t pos_current = 0;
uint16_t pos_target = 100;
uint8_t my_buffer = 10;

uint8_t speed=255;

unsigned long current_time = 0;
unsigned long past_time = 0;
unsigned long duration = 50;

void get_input(){
   /* if(Serial.available()){
    int temp = Serial.parseInt();
    if(temp!=0){
      if( (temp > 995) || (temp < 26) )
        Serial.println("Error! Entered Value Exceeds Limit\n Enter Value between 26-995");
      else 
        pos_target = temp;
    }
  } */
  pos_target = analogRead(A2);
}

void set_motor(){
  if(pos_current > pos_target+my_buffer){
    analogWrite(motor1, speed);
    digitalWrite(motor2, LOW);
  }
  else if(pos_current < pos_target-my_buffer){
    digitalWrite(motor1, LOW);
    analogWrite(motor2, speed);
  }
  else if((pos_current < pos_target+my_buffer)||(pos_current > pos_target-my_buffer)){
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  current_time = millis();
  pos_current = analogRead(pot);

  get_input();
  
  set_motor();

  if(current_time - past_time >= duration){
    past_time = current_time;
    Serial.println("Target:" + String(pos_target) + ",Lower:0,Higher:1024,Current:" + String(pos_current));
  }
}

