 #include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,10,11,12,13);

char serialBuffer[64];
int buffSize;
char ack[4];

void setup() {
	lcd.begin(16,2);
	Serial.begin(19200);
  	Serial.println("RDY");
}

void readSerialBuffer();

void loop() {
	if(Serial.available()){
		readSerialBuffer();
	}
}

void readSerialBuffer() {
	buffSize =0;
	while(Serial.available()){
		serialBuffer[buffSize] = Serial.read();
		buffSize++;
		delay(1);
	};
	buffSize--;
	serialBuffer[buffSize]='\0';

	Serial.println("ACK");
	Serial.println(buffSize);
	Serial.println(serialBuffer);

	lcd.clear();
	delay(100);
	lcd.print(serialBuffer);
}