void initialize_infrared(int pinNumber,int Mode) {
  // pinMode (IN_A0, INPUT);
  pinMode(pinNumber, Mode);
}


int read_infrared(int pinNumber) {
  int value = analogRead(pinNumber);  // reads the analog input from the IR distance sensor
  return value;
}