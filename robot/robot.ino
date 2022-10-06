// main code
#include "infrared.c"
#include "encodeur.c"
#include "ultrasonor.c"
#include "motor.c"

// infrarouge
const int infrared_pin = A0; // pin
int infrared_val; // value of the pin

// encodeur 
const int encodeur_pin = 11;
int encodeur_cnt=0;
int encodeur_min_time = 1; // definit la fréquence de mesure d'un tic
// définir une valeur de temps max avant de skipper 

//ultrasonor
const int trigPin = 3;
const int echoPin = 2;
int ultra_val;

// motor
const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;


void setup() {
  //general setup
  Serial.begin(9600);
  // infrared setup
  initialize_infrared(infrared_pin,INPUT);
  // encodeur setup
  initialize_encodeur(encodeur_pin,INPUT);
  // ultrasons
  initialize_ultrasonor(trigPin,OUTPUT,echoPin,INPUT);
  // motor
  initialize_motor(IN1,IN2,IN3,IN4,OUTPUT);
}

void loop() {
  // effectue une mesure du capteur infrarouge 
  infrared_val = read_infrared(infrared_pin);
  Serial.println("infrared_val :");
  Serial.println(infrared_val);



  // mesure de l'encodeur
  encodeur_cnt = read_encodeur(encodeur_pin,encodeur_cnt,encodeur_min_time); 
  Serial.println("encodeur_cnt :");
  Serial.println(encodeur_cnt);



  // mesure du capteur ultrasons
  ultra_val = read_ultrasonor(trigPin, echoPin);
  // Serial.printf("Ultrasound : %d cm",ultra_val);
  Serial.println("Ultrasonor :");
  Serial.println(ultra_val);
  // delay(2000);

  //motor
  activate_motor(IN1,IN2,IN3,IN4);

}
