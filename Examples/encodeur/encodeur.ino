
const int IN_D0 = 11; // digital input
int encodeur_cnt = 0; 

void setup() {
  // put your setup code here, to run once:
  pinMode (IN_D0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(IN_D0); // reads the analog input from the IR distance sensor
  if (value == 1){
    while (value == 1){
      value = digitalRead(IN_D0);      
    }
    encodeur_cnt +=1;
    Serial.println(encodeur_cnt); 
  }
}
