
 #include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,10,11,12,13);
// LCD Levels
byte lcd0[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F};
byte lcd1[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F};
byte lcd2[8] = {0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F};
byte lcd3[8] = {0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F};
byte lcd4[8] = {0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F};
byte lcd5[8] = {0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
byte lcd6[8] = {0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
byte lcd7[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};

char serialBuffer[64];
int buffSize;
char ack[4];
unsigned long frame=0;
unsigned long ttime;
unsigned long ttime1;
unsigned long ttime2;
unsigned long ttime3;

#define DFT_N 16
#define DFT_Nb2 9

// ReX coefficients for 16p-DFT
int8_t REx_cons[DFT_Nb2][DFT_N]={
{127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 },
{127, 117, 89, 48, 0, -49, -90, -118, -127, -118, -90, -49, 0, 48, 89, 117 },
{127, 89, 0, -90, -127, -90, 0, 89, 127, 89, 0, -90, -127, -90, 0, 89 },
{127, 48, -90, -118, 0, 117, 89, -49, -127, -49, 89, 117, 0, -118, -90, 48 },
{127, 0, -127, 0, 127, 0, -127, 0, 127, 0, -127, 0, 127, 0, -127, 0 },
{127, -49, -90, 117, 0, -118, 89, 48, -127, 48, 89, -118, 0, 117, -90, -49 },
{127, -90, 0, 89, -127, 89, 0, -90, 127, -90, 0, 89, -127, 89, 0, -90 },
{127, -118, 89, -49, 0, 48, -90, 117, -127, 117, -90, 48, 0, -49, 89, -118 },
{127, -127, 127, -127, 127, -127, 127, -127, 127, -127, 127, -127, 127, -127, 127, -127} 
};
// ImX coefficients for 16p-DFT (N/2+1)*N
int8_t IMx_cons[DFT_Nb2][DFT_N]={
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{0, -49, -90, -118, -127, -118, -90, -49, 0, 48, 89, 117, 127, 117, 89, 48 },
{0, -90, -127, -90, 0, 89, 127, 89, 0, -90, -127, -90, 0, 89, 127, 89 },
{0, -118, -90, 48, 127, 48, -90, -118, 0, 117, 89, -49, -127, -49, 89, 117 },
{0, -127, 0, 127, 0, -127, 0, 127, 0, -127, 0, 127, 0, -127, 0, 127 },
{0, -118, 89, 48, -127, 48, 89, -118, 0, 117, -90, -49, 127, -49, -90, 117 },
{0, -90, 127, -90, 0, 89, -127, 89, 0, -90, 127, -90, 0, 89, -127, 89 },
{0, -49, 89, -118, 127, -118, 89, -49, 0, 48, -90, 117, -127, 117, -90, 48 },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

// test 16p input signal
int8_t x[DFT_N] = {80,45,15,-1,-30,-57,-48,-14,22,64,88,36,-75,-127,-57,50};
int sig;

// Result Space
int32_t dft_ReX[DFT_Nb2];
int32_t dft_ImX[DFT_Nb2];
int16_t dftX[DFT_Nb2];
uint8_t lcd_lvl[DFT_Nb2];

// ~~~~~~~~~~~~~~ MAIN ~~~~~~~~~~~~~~~~
void setup() {
	lcd.createChar(0, lcd0);
	lcd.createChar(1, lcd1);
	lcd.createChar(2, lcd2);
	lcd.createChar(3, lcd3);
	lcd.createChar(4, lcd4);
	lcd.createChar(5, lcd5);
	lcd.createChar(6, lcd6);
	lcd.createChar(7, lcd7);

	lcd.begin(16,2); 
	Serial.begin(19200);
	Serial.println("RDY");

	delay(1000);
}

void readSerialBuffer();

void loop() {
	frame=millis();
	ttime = micros();
	// 16p DFT
	// Multiply and accumulate each bin in the Spectrum (0->N/2)
	// This takes in the "contribution" of input signal to various bins
	// It's just correleation of the input signal against various cosines/sines (each with kth frequency)
	for(int k =0;k<DFT_Nb2;k++) {
		dft_ReX[k]=0;
		dft_ImX[k]=0;

		for(int i =0;i<16;i++) {
			dft_ReX[k] += REx_cons[k][i] * x[i];
			dft_ImX[k] += -1 * IMx_cons[k][i] * x[i];
		}

		// Magnitude Correction - 1
		dft_ReX[k] = dft_ReX[k] >> 10;
		dft_ImX[k] = dft_ImX[k] >> 10;
	}

	// Magnitude Correction - 2
	dft_ReX[0] = dft_ReX[0] >> 1;
	dft_ReX[DFT_Nb2-1] = dft_ReX[DFT_Nb2-1] >> 1;
ttime1 = micros();
	//Magnitude Calculation
	for(int k =0;k<DFT_Nb2;k++) {
		dftX[k] = sqrt(dft_ReX[k]*dft_ReX[k] + dft_ImX[k]*dft_ImX[k]);
	}
ttime2 = micros();
	
	lcd.clear();
	lcd.setCursor(0,1);
	for(int k =0;k<DFT_Nb2;k++) {
		lcd_lvl[k]=0;
		for(int acc=8;acc<128;acc+=8){
			if(dftX[k]>=acc){lcd_lvl[k]++;}
			else break;
		}

		if(lcd_lvl[k]>7){
			lcd.setCursor(k,0);
			lcd.write(lcd_lvl[k]-8);
			lcd.setCursor(k,1);
			lcd.write(7);
		} else {
			lcd.write(lcd_lvl[k]);
		}
	}

ttime3 = micros();

	// Serial.println("REX");
	// for(int k =0;k<DFT_Nb2;k++) {Serial.println(dft_ReX[k]);}
	// Serial.println("IMX");
	// for(int k =0;k<DFT_Nb2;k++) {Serial.println(dft_ImX[k]);}

	// Serial.println("DFTX");
	// for(int k =0;k<DFT_Nb2;k++) {Serial.println(dftX[k]);}
	// Serial.println("LCD");
	// for(int k =0;k<DFT_Nb2;k++) {Serial.println(lcd_lvl[k]);}

	// Serial.println("TIME DFT");
	// Serial.println(ttime1-ttime);
	// Serial.println("TIME MAG");
	// Serial.println(ttime2-ttime1);
	// Serial.println("TIME LCD");
	// Serial.println(ttime3-ttime2);
	// Serial.println("TIME FULL");
	// Serial.println(ttime3-ttime);

	// Test
	// sig = analogRead(3);
	// Serial.println(sig);

	// Frame Guard
	while((millis()-frame)<33){	};
//while (1) {};
}