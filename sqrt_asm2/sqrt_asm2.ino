#include "sqrt.h"
extern void Increment_a_Number(void);

uint8_t a_number = 10;
char serialBuffer[64];

uint8_t res,res2,res3,res4,res5;
uint16_t temp[8];
uint16_t num= 0xFE01;

unsigned long ttime,time1,time2,time3,time4,time5;

void setup() {
	Serial.begin(19200);
  	Serial.println("RDY");
  	delay(500);
}

void loop() {
	ttime = micros();

	asm volatile (
		"ldi r20, 250 \n"    // A
		"ldi r21, 1 \n"		// B
		"ldi r26, lo8(res) \n"
		"ldi r27, hi8(res) \n"
		"clr r22 \n"		// ans
		"sloop: \n"
			"sub r20, r21 \n"
			"brcs sdone \n"
			"subi r21, -2 \n"
			"inc r22 \n"
			"rjmp sloop \n"
		
		"sdone: \n"
		"st X, r22 \n"
	);
	time1 = micros();

// // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 16 bit ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 	asm volatile (
// 		"ldi r16, 1 \n"    // Hold 1, will be used in addition later
// 		"clr r17 \n"	   // null register, often used in add/sub to propagate carry

// 		"clr r18 \n"		// remainder L
// 		"clr r19 \n"        // remainder H
// 		"ldi r20, 0xE4 \n"    // AL
// 		"ldi r21, 0x70 \n"    // AH
// 		"clr r22 \n"		// divisor L
// 		"clr r23 \n"		// divisor H
// 		"clr r24 \n"		// root
// 		"ldi r25, 8 \n"		// counter = bitDepth/2, in this case 16/2, as we work on 16 bit regs
		

// 		"ldi r30, lo8(res3) \n"		// result address
// 		"ldi r31, hi8(res3) \n"


		
// 		"mmloop: \n"	
// 			"clr r27 \n"		// clear mask
// 			"lsl r20 \n"		// A<<2, Get mask bits (higher 2 bits) into r17
// 			"rol r21 \n"
// 			"rol r27 \n"
// 			"lsl r20 \n"
// 			"rol r21 \n"
// 			"rol r27 \n"	

// 			"lsl r18 \n"		// Remainder<<2 , make space for next MSB 2 bits
// 			"rol r19 \n"
// 			"lsl r18 \n"
// 			"rol r19 \n"
// 			"add r18,r27 \n"	// Accumulate high bits into remainder
// 			"adc r19,r17 \n"

// 			"lsl r24 \n"		// root<<1 , make space for next bit
// 			"lsl r22 \n"		// divisor<<1 , make space for next bit
// 			"rol r23 \n"						

// 			"ori r22, 0x01 \n"	// Divisor = divisor+1 (this is a test bit). This is now the test divisor
// 								// There are only two combinations to check out as we are in binary.
// 								// that would be divisor and divisor++ (aka testdivisor)

// 								// Remainder - tdivisor 
// 			"cp r19,r23 \n"		// if(remainder < tdivisor)goto noadd , ie: divisor++ was not a good choice
// 			"brlo nnoadd \n"	// if (RemH < tdivH) goto noadd
// 			"brne madd  \n"		// if (RemH > tdivH) goto add
// 			"cp r18,r22 \n"		// if (RemL < tdivL) goto noadd (finally, we need to test this as RH and TH were equal)
// 			"brlo nnoadd \n"		

// 			"madd: \n"			
// 				"inc r24 \n"		//root++ (Add newBit to root), same as "ori r24,0x01". 
// 									// AVR is RISC processor. So, both take one cycle. Check instruction set
// 				"sub r18,r22 \n"	// Remainder = Remainder-testdivisor
// 				"sbc r19,r23 \n"

// 				"add r22, r16 \n"	// Divisor++, Note that divisor already has a 1 in LSB, so we simply add another
// 				"adc r23, r17 \n"	// coz, divisor += testBit*2 (here testBit is 1... duh!)

// 				"dec r25 \n"
// 				"brne mmloop \n"	
// 				"rjmp dddone \n"

// 			"nnoadd: \n"
// 				"andi r22, 0xFE \n"	// remove the LSB test bit
// 				"dec r25 \n"
// 				"brne mmloop \n"

// 		"dddone: \n"
// 		"st Z, r24 \n"		
// 	);
	time2 = micros();
	res5 = sqrt(num);
	time3 = micros();

	Serial.println("iterative_8");
	Serial.println(res);
	Serial.println(time1-ttime);
	Serial.println("longHand_16");
	Serial.println(res3);
	Serial.println(time2-time1);
	Serial.println("C_sqrt_16");
	Serial.println(res5);
	Serial.println(time3-time2);
	Serial.println(a_number);
	Increment_a_Number();
	Serial.println(a_number);

	while(1) { };

}