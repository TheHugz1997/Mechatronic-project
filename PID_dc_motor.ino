//Test sketch to try out FastPID

#include <FastPID.h>

// Define Motor A connections to L298N
int enA = 5;
int in1 = 4;
int in2 = 7;
// Define Motor B connections to L298N
int enB = 6;
int in3 = 8;
int in4 = 9;


const int encoder1 = 2; // define
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
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Set interrupt pins to inputs
  pinMode(encoder1, INPUT);// setting up encoder pin as input
  pinMode(encoder2, INPUT);// setting up encoder pin as input

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

  attachInterrupt(digitalPinToInterrupt(encoder1), count1, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoder2), count2, FALLING);
}

void loop() {
  // Motors forward for 10 seconds
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);


  pulse1 = 0;
  pulse2 = 0;

  delay(10*1000);
}

ISR(TIMER1_COMPA_vect){
  static int pError;
  pError = 0;
  pError = pulse1 - pulse2;
  uint8_t output = driveStraight.step(setpoint, pError);

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