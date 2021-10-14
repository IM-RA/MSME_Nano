#include <Arduino.h>

#define outputA 27
#define outputB 26

int counter = 0; 
int aState;
int aLastState;  

void setup() { 
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  
  Serial.begin (115200);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);   
} 

void loop() { 
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured   
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
  if( (aLastState != aState) && (aState == LOW) ){
    if(digitalRead(outputB) == LOW){
      counter --;
    }
    else{
      counter ++;
    }
  }
  aLastState = aState;
  Serial.println("Counter:" + String(counter));
}