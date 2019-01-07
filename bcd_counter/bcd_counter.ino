/*
  3bit BCD counter
  
 */
 
// Pin 11,12,13 has an LED connected
int led[3] = {13,12,11};
int counter = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int i=0;i<3;i++){
    pinMode(led[i], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
    counter %= 8;
    int b0 = counter & 0b001;
    int b1 = counter & 0b010; b1 = b1 >> 1;
    int b2 = counter & 0b100; b2 = b2 >> 2;
    digitalWrite(led[0], b0);
    digitalWrite(led[1], b1);
    digitalWrite(led[2], b2);
    counter++;

    delay(1000);
}
