/*
  Blinky
  
 */
 
// Pin 11,12,13 has an LED connected
int led[3] = {11,12,13};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int i=0;i<=2;i++){
    pinMode(led[i], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i=0;i<=2;i++){
    digitalWrite(led[i], HIGH);
    delay(500);
    digitalWrite(led[i], LOW);
    delay(500);
  }
}
