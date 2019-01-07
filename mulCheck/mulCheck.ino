char serialBuffer[64];
int buffSize;
char ack[4];

int8_t a[] = { 0x3F, 0x3F };
int16_t c=0;

void setup() {
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

	if(serialBuffer[0] == 'M' && serialBuffer[1] == 'U' && serialBuffer[2] == 'L') {

		//uint16_t c = (uint16_t)a * (uint16_t)b;
		asm  volatile (
				"push r0 \n"
				"push r1 \n"
				"push r16 \n"
				"push r17 \n"

				"ldi r26,lo8(a) \n"
				"ldi r27,hi8(a) \n"
				"ldi r28,lo8(c) \n"
				"ldi r29,hi8(c) \n"

				"ld r16,X+ \n"
				"ld r17,X \n"

				"fmuls r16,r17 \n"

				// "st Y+,r0 \n"
				// "st Y,r1 \n"
				"st Y,r1 \n"

				"pop r17 \n"
				"pop r16 \n"
				"pop r1 \n"
				"pop r0 \n"
			);

		Serial.println(a[0],HEX);
		Serial.println(a[1],HEX);
		Serial.println(c,HEX);
		Serial.println(c,BIN);
	}
}