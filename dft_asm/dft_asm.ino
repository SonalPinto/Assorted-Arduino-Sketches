
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
unsigned long ttime, ttime1, ttime2;

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

// Result Space
int8_t dft_ReX[DFT_Nb2];
int8_t dft_ImX[DFT_Nb2];
uint16_t dft_ReX2[DFT_Nb2];
uint16_t dft_ImX2[DFT_Nb2];
uint8_t dftX[DFT_Nb2];
uint8_t lcd_lvl[DFT_Nb2];

 
// ~~~~~~~~~~~~~~ INIT ~~~~~~~~~~~~~~~~
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
}

void readSerialBuffer();

// ~~~~~~~~~~~~~~ MAIN ~~~~~~~~~~~~~~~~
void loop() {

ttime = micros();
	// 16p DFT
	// Multiply and accumulate each bin in the Spectrum (0->N/2)
	// This takes in the "contribution" of input signal to various bins
	// It's just correleation of the input signal against various cosines/sines (each with kth frequency)
	asm volatile (
	// Save processor state onto stack
	"push r2 \n"
	"push r3 \n"
	"push r4 \n"
	"push r5 \n"
	"push r6 \n"
	"push r7 \n"
	"push r8 \n"
	"push r9 \n"
	"push r10 \n"
	"push r11 \n"
	"push r12 \n"
	"push r13 \n"
	"push r14 \n"
	"push r15 \n"
	"push r16 \n"
	"push r17 \n"
	"push r28 \n"
	"push r29 \n"

//~~~~~~~~~~~~~ DFT CALC ~~~~~~~~~~~~~~~~~~~
// Calc ReX
	// Load addresses: X=[x], Y=[REx_cons], Z=[dft_ReX]
	"ldi r30, lo8(dft_ReX) \n" 
	"ldi r31, hi8(dft_ReX) \n" 
	"ldi r28, lo8(REx_cons) \n" 
	"ldi r29, hi8(REx_cons) \n" 
	"ldi r24, lo8(dft_ReX2) \n" 
	"ldi r25, hi8(dft_ReX2) \n" 
	// Loop through 0 - N/2 frequency bins
	"ldi r16, 9 \n"
	"kloop: \n"
		"clr r8 \n"
		"clr r9 \n"
		// reset x address
		"ldi R26, lo8(x) \n" 
		"ldi R27, hi8(x) \n" 

		// // Loop through 16 samples of x
		"ldi R17, 16 \n"
			"iloop: \n"
			// r20 <- [ReX_cons], Y++
			"ld R20, Y+ \n"
			// r21 <- [x], X++
			"ld R21, X+ \n"
			// r9:8 = mac(r20*r21)
			"fmuls R20, R21 \n"
			"asr r1 \n"	// Overflow Gaurd + div by 2 (Also Magnitude correction)
			"ror r0 \n"
			"asr r1 \n"	// Overflow Gaurd + div by 2 (Also Magnitude Correction)
			"ror r0 \n"
			"add R8, R0 \n"
			"adc R9, R1 \n"
			"dec R17 \n"
		"brne iloop \n"	
		// Discard the lower 8 bytes as we scale from 2e-15 to 2e-7 (aka x2e8)
		// store mac'd kth bin back
		// Final Magnitude Correction. Overall the whole thing must be divided by N/2. In this case 8. 
		// Since, previously I have already div'd by 4 (2 for each rightShift). I just need one more
		"asr r9 \n"
		// special case if k=0 or k=N/2, then it has to be div by 2 again.
		// if(r16==9 || r16==0) {r9>>1;}
		"cpi r16, 9 \n"
			"breq isTrue \n"
		"cpi r16, 0 \n"
			"breq isTrue \n"
			"rjmp isFalse \n"
		"isTrue: \n"
		"asr r9 \n"

		"isFalse: \n"
		"st Z+, r9 \n"

		// Store ReX^2 into another accumulator. Will be used for absolute magnitude calc
		"clr r2 \n"
		"clr r3 \n"
		"mov r20,r9 \n"
		"muls r20,r20 \n"
		"add r2, r0 \n"
		"adc r3, r1 \n"
		"movw r26, r24 \n"
		"st X+ , r2 \n"
		"st X+ , r3 \n"
		"movw r24, r26 \n"

		"dec R16 \n"
	"brne kloop \n"

// Calc ImX
	// Load addresses: X=[x], Y=[ImX_cons], Z=[dft_ImX]
	"ldi r30, lo8(dft_ImX) \n" 
	"ldi r31, hi8(dft_ImX) \n" 
	"ldi R28, lo8(IMx_cons) \n" 
	"ldi R29, hi8(IMx_cons) \n" 
	"ldi r24, lo8(dft_ImX2) \n" 
	"ldi r25, hi8(dft_ImX2) \n" 
	// Loop through 0 - N/2 frequency bins
	"ldi r16, 9 \n"
	"kkloop: \n"
		"clr r8 \n"
		"clr r9 \n"
		// reset x address
		"ldi R26, lo8(x) \n" 
		"ldi R27, hi8(x) \n" 

		// // Loop through 16 samples of x
		"ldi R17, 16 \n"
		"iiloop: \n"
			// r20 <- [ImX_cons], Y++
			"ld R20, Y+ \n"
			// -1 * r20 , Becuase all ImX has to accumulated * -1
			"neg r20 \n"
			// r21 <- [x], X++
			"ld R21, X+ \n"
			// r9:8 = mac(r20*r21)
			"fmuls R20, R21 \n"
			"asr r1 \n"
			"ror r0 \n"
			"asr r1 \n"
			"ror r0 \n"
			"add R8, R0 \n"
			"adc R9, R1 \n"
			"dec R17 \n"
		"brne iiloop \n"
		// Discard the lower 8 bytes as we scale from 2e-15 to 2e-7 (aka x2e8)
		// store mac'd kth bin back
		//"st Z+, r8 \n"
		"asr r9 \n"
		"st Z+, r9 \n"
		
		// Store ImX^2 into another accumulator. Will be used for absolute magnitude calc
		"clr r2 \n"
		"clr r3 \n"
		"mov r20,r9 \n"
		"muls r20,r20 \n"
		"add r2, r0 \n"
		"adc r3, r1 \n"
		"movw r26, r24 \n"
		"st X+ , r2 \n"
		"st X+ , r3 \n"
		"movw r24, r26 \n"

		"dec R16 \n"
	"brne kkloop \n"



//~~~~~~~~~~~~~ MAG CALC ~~~~~~~~~~~~~~~~~~~
	"ldi r26, lo8(dftX) \n"
	"ldi r27, hi8(dftX) \n"
	"ldi r28, lo8(dft_ReX2) \n"
	"ldi r29, hi8(dft_ReX2) \n"
	"ldi r30, lo8(dft_ImX2) \n"
	"ldi r31, hi8(dft_ImX2) \n"

	"ldi r16, 1 \n"    // Hold 1, will be used in addition later
	"ldi r17, 9 \n"		// main loop counter
	"mov r4, r17 \n"	
	"clr r17 \n"	   // null register, often used in add/sub to propagate carry


"dftXloop: \n"
	"clr r18 \n"		// remainder L
	"clr r19 \n"        // remainder H
	"ld r20, Y+ \n"    // ReX2 L
	"ld r21, Y+ \n"    // ReX2 H
	"ld r22, Z+ \n"    // ImX2 L
	"ld r23, Z+ \n"    // ImX2 H
	"add r20,r22 \n "	// ReX^2 + ImX^2 - This is our "A", we need to find the square root of "A"
	"adc r21,r23 \n"

	"clr r22 \n"		// divisor L
	"clr r23 \n"		// divisor H
	"clr r24 \n"		// root
	"ldi r25, 8 \n"		// counter = bitDepth/2, in this case 16/2, as we work on 16 bit regs
	
	"sqrtLoop: \n"	
		"clr r2 \n"		// clear mask
		"lsl r20 \n"		// A<<2, Get mask bits (higher 2 bits) into r17
		"rol r21 \n"
		"rol r2 \n"
		"lsl r20 \n"
		"rol r21 \n"
		"rol r2 \n"	

		"lsl r18 \n"		// Remainder<<2 , make space for next MSB 2 bits
		"rol r19 \n"
		"lsl r18 \n"
		"rol r19 \n"
		"add r18,r2 \n"	// Accumulate high bits into remainder
		"adc r19,r17 \n"

		"lsl r24 \n"		// root<<1 , make space for next bit
		"lsl r22 \n"		// divisor<<1 , make space for next bit
		"rol r23 \n"						

		"ori r22, 0x01 \n"	// Divisor = divisor+1 (this is a test bit). This is now the test divisor
							// There are only two combinations to check out as we are in binary.
							// that would be divisor and divisor++ (aka testdivisor)

							// Remainder - tdivisor 
		"cp r19,r23 \n"		// if(remainder < tdivisor)goto noadd , ie: divisor++ was not a good choice
		"brlo sqrtNoAdd \n"	// if (RemH < tdivH) goto noadd
		"brne madd  \n"		// if (RemH > tdivH) goto add
		"cp r18,r22 \n"		// if (RemL < tdivL) goto noadd (finally, we need to test this as RH and TH were equal)
		"brlo sqrtNoAdd \n"		

		"madd: \n"			
			"inc r24 \n"		//root++ (Add newBit to root), same as "ori r24,0x01". 
								// AVR is RISC processor. So, both take one cycle. Check instruction set
			"sub r18,r22 \n"	// Remainder = Remainder-testdivisor
			"sbc r19,r23 \n"

			"add r22, r16 \n"	// Divisor++, Note that divisor already has a 1 in LSB, so we simply add another
			"adc r23, r17 \n"	// coz, divisor += testBit*2 (here testBit is 1... duh!)

			"dec r25 \n"
			"brne sqrtLoop \n"	
			"rjmp sqrtDone \n"

		"sqrtNoAdd: \n"
			"andi r22, 0xFE \n"	// remove the LSB test bit
			"dec r25 \n"
			"brne sqrtLoop \n"

	"sqrtDone: \n"
	"st X+, r24 \n"	

	"dec r4 \n"
	"brne dftXloop \n"


	// Restore processor state from stack
	"pop r29 \n"
	"pop r28 \n"
	"pop r17 \n"
	"pop r16 \n"
	"pop r15 \n"
	"pop r14 \n"
	"pop r13 \n"
	"pop r12 \n"
	"pop r11 \n"
	"pop r10 \n"
	"pop r9 \n"
	"pop r8 \n"
	"pop r7 \n"
	"pop r6 \n"
	"pop r5 \n"
	"pop r4 \n"
	"pop r3 \n"
	"pop r2 \n"
	"clr r1 \n"
	);

ttime1 = micros();

// Put LCD code here
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

ttime2 = micros();

	// Serial.println("REX");
	// for(int k =0;k<DFT_Nb2;k++) {Serial.println(dft_ReX[k]);}
	// Serial.println("IMX");
	// for(int k =0;k<DFT_Nb2;k++) {Serial.println(dft_ImX[k]);}
	Serial.println("DFTX");
	for(int k =0;k<DFT_Nb2;k++) {Serial.println(dftX[k]);}
	// 		Serial.println("ReX2");
	// for(int k =0;k<DFT_Nb2;k++) {Serial.println(dft_ReX2[k]);}
	// 		Serial.println("ImX2");
	// for(int k =0;k<DFT_Nb2;k++) {Serial.println(dft_ImX2[k]);}

	Serial.println("TIME DFT");
	Serial.println(ttime1-ttime);
	Serial.println("TIME LCD");
	Serial.println(ttime2-ttime1);
	Serial.println("TIME FULL");
	Serial.println(ttime2-ttime);

	while(1){};
	
}