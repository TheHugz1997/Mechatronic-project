#include <FastPID.h>

// variable for the duration of sound wave 
#define echoPin_straight 10 
#define trigPin_straight 11
long duration_straight; 
int distance_straight; 

// variable for the duration of sound wave 
#define echoPin_right 12
#define trigPin_right 13
long duration_right; 
int distance_right;

// Define Motor A connections to L298N
int enA = 5;
int in1 = 4;    
int in2 = 7;
// Define Motor B connections to L298N
int enB = 6;
int in3 = 8;
int in4 = 9;

//define variable and pins for encoders
const int encoder1 = 2;
const int encoder2 = 3;
volatile int pulse1;
volatile int pulse2;
int motorSpeed = 120;
int setpoint;

float Kp=0.6, Ki=0.4, Kd=0.0, Hz=4.0;
int output_bits = 8;
bool output_signed = false;

FastPID driveStraight(Kp, Ki, Kd, Hz, output_bits, output_signed);

void setup() {
  //set encoders pins
  pinMode(trigPin_straight, OUTPUT);
  pinMode(echoPin_straight, INPUT);
  pinMode(trigPin_right, OUTPUT); 
  pinMode(echoPin_right, INPUT);

  //set L198N pins as output
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

 // setting encoder pin as input
  pinMode(encoder1, INPUT);
  pinMode(encoder2, INPUT);

  cli();//stop interrupts

  //set timer1 interrupt at 4Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 4hz increments
  OCR1A = 3905;// = (16*10^6) / (4*1024) - 1 (must be <65536)
  // turn on CTC mode 
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();//allow interrupts

  pulse1 = 0;
  pulse2 = 0;
  setpoint = 0;  
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // Set initial speed of Motors
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);

  //attach interruption with encoders
  attachInterrupt(digitalPinToInterrupt(encoder1), count1, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoder2), count2, FALLING);
}

void loop() {
  //  ultrasonic sensor of the straight will mesure the distance between the car and an obstacles of the front
  digitalWrite(trigPin_straight, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin_straight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_straight, LOW);
  duration_straight = pulseIn(echoPin_straight, HIGH);
  distance_straight = duration_straight * 0.034 / 2;  


  if (distance_straight<10){//if an obstacle is deteced on the front (<10 cm)
    //  ultrasonic sensor of the left will mesure the distance between the car and an obstacles of the left
    digitalWrite(trigPin_right, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_right, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_right, LOW);
    duration_right = pulseIn(echoPin_right, HIGH);
    distance_right = duration_right * 0.034 / 2;  

    if (distance_right<10){
      //if an obstable is detected on the frot and also on the left side
      //one motor will stop and another will turn, the car rotate on the right side during 0.5 seconde
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500);

    }
    else{
      //if an obstable is detected on the frot and none at the left side
      //one motor will stop and another will turn, the car rotate on the left side during 0.5 seconde
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      delay(500);
    }
  }
  else{
    //if nothing is detected on the front, the car will run straightly
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH );
    delay(500);
  }

  pulse1 = 0;
  pulse2 = 0;

 
}

ISR(TIMER1_COMPA_vect){
  
  static int pError;
  pError = 0;
  pError = pulse1 - pulse2;
  uint8_t output = driveStraight.step(setpoint, pError);
  //set motor speed depend the difference between the real speed and desire speed
  analogWrite(enA, (motorSpeed - output));
  analogWrite(enB, (motorSpeed + output));

  
}

void count1(){
  // counting the number of pulses for encoder 1
  pulse1++;
}

void count2(){
  // counting the number of pulses for encoder 2
  pulse2++;
}