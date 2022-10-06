// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
#include <Wire.h>


// 0x27 is the I2C address. This address might be different.

const int IN_A0 = A0; // analog input


void setup() {
  pinMode (IN_A0, INPUT);
  Serial.begin(9600);
  
}

int value_A0;

void loop() {

  value_A0 = analogRead(IN_A0); // reads the analog input from the IR distance sensor
  Serial.print("value: " );
  Serial.println(value_A0);
  
  delay(1000);
}