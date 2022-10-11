#include "globals.h"

void initialize_motor(int IN1,int IN2,int IN3,int IN4,int mode){
  // #define OUTPUT 1
   pinMode(IN1, mode);
   pinMode(IN2, mode);
   pinMode(IN3, mode);
   pinMode(IN4, mode);
}


void activate_motor(int IN1,int IN2,int IN3,int IN4){
  #define LOW 0
  #define HIGH 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  isMoving = 1;
}

