void initialize_ultrasonor(int trigPin,int trigMode, int echoPin, int echoMode){
  pinMode(trigPin,trigMode);
  pinMode(echoPin,echoMode);
}

int read_ultrasonor(int trigPin, int echoPin){
  long duration; // variable for the duration of sound wave travel
  int distance; // variable for the distance measurement
  #define LOW 0
  #define HIGH 1
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  // Serial.print("Ultrasound : ");
  // Serial.print(distance);
  // Serial.println(" cm");
  return distance;

}