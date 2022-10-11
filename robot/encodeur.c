void initialize_encodeur(int pinNumber, int Mode){
  pinMode(pinNumber, Mode);
}
  
int read_encodeur(int pinNumber,int encodeur_cnt,int encodeur_min_time){
  int time_since_detected = 0;
  int value = digitalRead(pinNumber); // reads the analog input from the IR distance sensor
  if (value == 1){
    while (value == 1){
      value = digitalRead(pinNumber);    
      time_since_detected++;  
      if (time_since_detected > valeur max temps mort){

      }
    }
    if (time_since_detected > encodeur_min_time){
      encodeur_cnt +=1;
    } 
  }
  return encodeur_cnt;
}
  
