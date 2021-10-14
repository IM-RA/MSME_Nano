#include <Arduino.h>
#include <Servo.h>

#define NUM_MOTOR 6

uint8_t all_end_flag=0x00;
uint8_t all_done=0x00;

struct myservo{
  Servo servo;
  uint8_t previous_position = 0;
  uint8_t working_position = 0;
  uint8_t target_position = 0;
  uint8_t call_order;
};
struct myservo new_motor[NUM_MOTOR];

uint8_t posistion[NUM_MOTOR][2] = {{0,180},{0,45},{45,135},{90,0},{135,180},{80,35}};
uint8_t larger_number = 0;

void motor_move(uint8_t i){
  //Serial.println("Motor=>"+String(i)+"Position="+String(new_motor[i].working_position));
  new_motor[i].servo.write(new_motor[i].working_position);
  if(new_motor[i].working_position < new_motor[i].target_position){
    new_motor[i].working_position++;
  } else if(new_motor[i].working_position > new_motor[i].target_position){
    new_motor[i].working_position--;
  } else{
    all_end_flag = all_end_flag | (1 << i);
    //Serial.print("End=>");
    //Serial.println(all_end_flag);
    if(all_end_flag == all_done){
      //Serial.println("Swap");
      for(int i=0;i<NUM_MOTOR;i++){
        uint8_t temp;
        temp = new_motor[i].target_position;    
        new_motor[i].target_position = new_motor[i].previous_position;
        new_motor[i].previous_position = temp;
      }
      all_end_flag =0x00;       
    }
  }
}

void call_order(){
  for(uint8_t i=1;i<=larger_number;i++){
    for(uint8_t j=0;j<NUM_MOTOR;j++){
      if(i%new_motor[j].call_order==0||new_motor[j].call_order==0){
        motor_move(j);
      }
    }
  }
}

void call_priority(){
  uint8_t smallest_number = 255;
  for(int i=0;i<NUM_MOTOR;i++){
    new_motor[i].call_order = abs(new_motor[i].target_position-new_motor[i].previous_position);
    //Serial.println("MotorCallOrderSub=>"+String(i)+"=>"+String(new_motor[i].call_order));
    if(smallest_number>new_motor[i].call_order && new_motor[i].call_order!=0){
      smallest_number = new_motor[i].call_order;
    }
  }
  //Serial.println("Smallest=>"+String(smallest_number));
  for(int i=0;i<NUM_MOTOR;i++){
    new_motor[i].call_order = new_motor[i].call_order/smallest_number;  
    //Serial.println("MotorCallOrderLCM=>"+String(i)+"=>"+String(new_motor[i].call_order));
    if(larger_number<new_motor[i].call_order){
      larger_number = new_motor[i].call_order;
    }
  }
  //Serial.println("Largest=>"+String(larger_number));
  for(int i=0;i<NUM_MOTOR;i++){
    if(new_motor[i].call_order!=0){
      new_motor[i].call_order=(larger_number/new_motor[i].call_order);
    }
    //Serial.println("MotorCallOrderFinal=>"+String(i)+"=>"+String(new_motor[i].call_order));
  }
}

void set_positions(){
  for(int i=0;i<NUM_MOTOR;i++){
    new_motor[i].previous_position=posistion[i][0];
    new_motor[i].target_position=posistion[i][1];
    new_motor[i].working_position = new_motor[i].previous_position;
    //Serial.println("Motor"+String(i));
    //Serial.println("Pre_Pos"+String(new_motor[i].previous_position));
    //Serial.println("Tar_Pos"+String(new_motor[i].target_position));
    //Serial.println("Wor_Pos"+String(new_motor[i].working_position));
  }
}

void set_pins(uint8_t pin){
  for(int i=0;i<NUM_MOTOR;i++){
    new_motor[i].servo.attach(pin-i);
    //Serial.println("Motor"+String(i)+"=>"+String(pin-i));
    all_done = all_done | (1 << i);
  }
}

void setup() {
  Serial.begin(9600);
  set_pins(11);
  set_positions();
  call_priority();
  call_order();
}

void loop() {
  call_order();
  Serial.println( "Motor1:" + String(new_motor[0].working_position) +
                  ",Motor2:" + String(new_motor[1].working_position) +
                  ",Motor3:" + String(new_motor[2].working_position) +
                  ",Motor4:" + String(new_motor[3].working_position) +
                  ",Motor5:" + String(new_motor[4].working_position) +
                  ",Motor6:" + String(new_motor[5].working_position) );
  delay(50);
}