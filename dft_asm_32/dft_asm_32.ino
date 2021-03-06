
 #include <LiquidCrystal.h>
#include <avr/pgmspace.h>

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

#define DFT_N 64
#define DFT_Nb2 33

// ReX coefficients for 32p-DFT
prog_int8_t REx_cons[DFT_Nb2][DFT_N] PROGMEM={
{127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127},
{127,126,124,121,117,112,105,98,89,80,70,59,48,36,24,12,0,-13,-25,-37,-49,-60,-71,-81,-90,-99,-106,-113,-118,-122,-125,-127,-127,-127,-125,-122,-118,-113,-106,-99,-90,-81,-71,-60,-49,-37,-25,-13,0,12,24,36,48,59,70,80,89,98,105,112,117,121,124,126},
{127,124,117,105,89,70,48,24,0,-25,-49,-71,-90,-106,-118,-125,-127,-125,-118,-106,-90,-71,-49,-25,0,24,48,70,89,105,117,124,127,124,117,105,89,70,48,24,0,-25,-49,-71,-90,-106,-118,-125,-127,-125,-118,-106,-90,-71,-49,-25,0,24,48,70,89,105,117,124},
{127,121,105,80,48,12,-25,-60,-90,-113,-125,-127,-118,-99,-71,-37,0,36,70,98,117,126,124,112,89,59,24,-13,-49,-81,-106,-122,-127,-122,-106,-81,-49,-13,24,59,89,112,124,126,117,98,70,36,0,-37,-71,-99,-118,-127,-125,-113,-90,-60,-25,12,48,80,105,121},
{127,117,89,48,0,-49,-90,-118,-127,-118,-90,-49,0,48,89,117,127,117,89,48,0,-49,-90,-118,-127,-118,-90,-49,0,48,89,117,127,117,89,48,0,-49,-90,-118,-127,-118,-90,-49,0,48,89,117,127,117,89,48,0,-49,-90,-118,-127,-118,-90,-49,0,48,89,117},
{127,112,70,12,-49,-99,-125,-122,-90,-37,24,80,117,126,105,59,0,-60,-106,-127,-118,-81,-25,36,89,121,124,98,48,-13,-71,-113,-127,-113,-71,-13,48,98,124,121,89,36,-25,-81,-118,-127,-106,-60,0,59,105,126,117,80,24,-37,-90,-122,-125,-99,-49,12,70,112},
{127,105,48,-25,-90,-125,-118,-71,0,70,117,124,89,24,-49,-106,-127,-106,-49,24,89,124,117,70,0,-71,-118,-125,-90,-25,48,105,127,105,48,-25,-90,-125,-118,-71,0,70,117,124,89,24,-49,-106,-127,-106,-49,24,89,124,117,70,0,-71,-118,-125,-90,-25,48,105},
{127,98,24,-60,-118,-122,-71,12,89,126,105,36,-49,-113,-125,-81,0,80,124,112,48,-37,-106,-127,-90,-13,70,121,117,59,-25,-99,-127,-99,-25,59,117,121,70,-13,-90,-127,-106,-37,48,112,124,80,0,-81,-125,-113,-49,36,105,126,89,12,-71,-122,-118,-60,24,98},
{127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89},
{127,80,-25,-113,-118,-37,70,126,89,-13,-106,-122,-49,59,124,98,0,-99,-125,-60,48,121,105,12,-90,-127,-71,36,117,112,24,-81,-127,-81,24,112,117,36,-71,-127,-90,12,105,121,48,-60,-125,-99,0,98,124,59,-49,-122,-106,-13,89,126,70,-37,-118,-113,-25,80},
{127,70,-49,-125,-90,24,117,105,0,-106,-118,-25,89,124,48,-71,-127,-71,48,124,89,-25,-118,-106,0,105,117,24,-90,-125,-49,70,127,70,-49,-125,-90,24,117,105,0,-106,-118,-25,89,124,48,-71,-127,-71,48,124,89,-25,-118,-106,0,105,117,24,-90,-125,-49,70},
{127,59,-71,-127,-49,80,124,36,-90,-122,-25,98,117,12,-106,-113,0,112,105,-13,-118,-99,24,121,89,-37,-125,-81,48,126,70,-60,-127,-60,70,126,48,-81,-125,-37,89,121,24,-99,-118,-13,105,112,0,-113,-106,12,117,98,-25,-122,-90,36,124,80,-49,-127,-71,59},
{127,48,-90,-118,0,117,89,-49,-127,-49,89,117,0,-118,-90,48,127,48,-90,-118,0,117,89,-49,-127,-49,89,117,0,-118,-90,48,127,48,-90,-118,0,117,89,-49,-127,-49,89,117,0,-118,-90,48,127,48,-90,-118,0,117,89,-49,-127,-49,89,117,0,-118,-90,48},
{127,36,-106,-99,48,126,24,-113,-90,59,124,12,-118,-81,70,121,0,-122,-71,80,117,-13,-125,-60,89,112,-25,-127,-49,98,105,-37,-127,-37,105,98,-49,-127,-25,112,89,-60,-125,-13,117,80,-71,-122,0,121,70,-81,-118,12,124,59,-90,-113,24,126,48,-99,-106,36},
{127,24,-118,-71,89,105,-49,-125,0,124,48,-106,-90,70,117,-25,-127,-25,117,70,-90,-106,48,124,0,-125,-49,105,89,-71,-118,24,127,24,-118,-71,89,105,-49,-125,0,124,48,-106,-90,70,117,-25,-127,-25,117,70,-90,-106,48,124,0,-125,-49,105,89,-71,-118,24},
{127,12,-125,-37,117,59,-106,-81,89,98,-71,-113,48,121,-25,-127,0,126,24,-122,-49,112,70,-99,-90,80,105,-60,-118,36,124,-13,-127,-13,124,36,-118,-60,105,80,-90,-99,70,112,-49,-122,24,126,0,-127,-25,121,48,-113,-71,98,89,-81,-106,59,117,-37,-125,12},
{127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0},
{127,-13,-125,36,117,-60,-106,80,89,-99,-71,112,48,-122,-25,126,0,-127,24,121,-49,-113,70,98,-90,-81,105,59,-118,-37,124,12,-127,12,124,-37,-118,59,105,-81,-90,98,70,-113,-49,121,24,-127,0,126,-25,-122,48,112,-71,-99,89,80,-106,-60,117,36,-125,-13},
{127,-25,-118,70,89,-106,-49,124,0,-125,48,105,-90,-71,117,24,-127,24,117,-71,-90,105,48,-125,0,124,-49,-106,89,70,-118,-25,127,-25,-118,70,89,-106,-49,124,0,-125,48,105,-90,-71,117,24,-127,24,117,-71,-90,105,48,-125,0,124,-49,-106,89,70,-118,-25},
{127,-37,-106,98,48,-127,24,112,-90,-60,124,-13,-118,80,70,-122,0,121,-71,-81,117,12,-125,59,89,-113,-25,126,-49,-99,105,36,-127,36,105,-99,-49,126,-25,-113,89,59,-125,12,117,-81,-71,121,0,-122,70,80,-118,-13,124,-60,-90,112,24,-127,48,98,-106,-37},
{127,-49,-90,117,0,-118,89,48,-127,48,89,-118,0,117,-90,-49,127,-49,-90,117,0,-118,89,48,-127,48,89,-118,0,117,-90,-49,127,-49,-90,117,0,-118,89,48,-127,48,89,-118,0,117,-90,-49,127,-49,-90,117,0,-118,89,48,-127,48,89,-118,0,117,-90,-49},
{127,-60,-71,126,-49,-81,124,-37,-90,121,-25,-99,117,-13,-106,112,0,-113,105,12,-118,98,24,-122,89,36,-125,80,48,-127,70,59,-127,59,70,-127,48,80,-125,36,89,-122,24,98,-118,12,105,-113,0,112,-106,-13,117,-99,-25,121,-90,-37,124,-81,-49,126,-71,-60},
{127,-71,-49,124,-90,-25,117,-106,0,105,-118,24,89,-125,48,70,-127,70,48,-125,89,24,-118,105,0,-106,117,-25,-90,124,-49,-71,127,-71,-49,124,-90,-25,117,-106,0,105,-118,24,89,-125,48,70,-127,70,48,-125,89,24,-118,105,0,-106,117,-25,-90,124,-49,-71},
{127,-81,-25,112,-118,36,70,-127,89,12,-106,121,-49,-60,124,-99,0,98,-125,59,48,-122,105,-13,-90,126,-71,-37,117,-113,24,80,-127,80,24,-113,117,-37,-71,126,-90,-13,105,-122,48,59,-125,98,0,-99,124,-60,-49,121,-106,12,89,-127,70,36,-118,112,-25,-81},
{127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90},
{127,-99,24,59,-118,121,-71,-13,89,-127,105,-37,-49,112,-125,80,0,-81,124,-113,48,36,-106,126,-90,12,70,-122,117,-60,-25,98,-127,98,-25,-60,117,-122,70,12,-90,126,-106,36,48,-113,124,-81,0,80,-125,112,-49,-37,105,-127,89,-13,-71,121,-118,59,24,-99},
{127,-106,48,24,-90,124,-118,70,0,-71,117,-125,89,-25,-49,105,-127,105,-49,-25,89,-125,117,-71,0,70,-118,124,-90,24,48,-106,127,-106,48,24,-90,124,-118,70,0,-71,117,-125,89,-25,-49,105,-127,105,-49,-25,89,-125,117,-71,0,70,-118,124,-90,24,48,-106},
{127,-113,70,-13,-49,98,-125,121,-90,36,24,-81,117,-127,105,-60,0,59,-106,126,-118,80,-25,-37,89,-122,124,-99,48,12,-71,112,-127,112,-71,12,48,-99,124,-122,89,-37,-25,80,-118,126,-106,59,0,-60,105,-127,117,-81,24,36,-90,121,-125,98,-49,-13,70,-113},
{127,-118,89,-49,0,48,-90,117,-127,117,-90,48,0,-49,89,-118,127,-118,89,-49,0,48,-90,117,-127,117,-90,48,0,-49,89,-118,127,-118,89,-49,0,48,-90,117,-127,117,-90,48,0,-49,89,-118,127,-118,89,-49,0,48,-90,117,-127,117,-90,48,0,-49,89,-118},
{127,-122,105,-81,48,-13,-25,59,-90,112,-125,126,-118,98,-71,36,0,-37,70,-99,117,-127,124,-113,89,-60,24,12,-49,80,-106,121,-127,121,-106,80,-49,12,24,-60,89,-113,124,-127,117,-99,70,-37,0,36,-71,98,-118,126,-125,112,-90,59,-25,-13,48,-81,105,-122},
{127,-125,117,-106,89,-71,48,-25,0,24,-49,70,-90,105,-118,124,-127,124,-118,105,-90,70,-49,24,0,-25,48,-71,89,-106,117,-125,127,-125,117,-106,89,-71,48,-25,0,24,-49,70,-90,105,-118,124,-127,124,-118,105,-90,70,-49,24,0,-25,48,-71,89,-106,117,-125},
{127,-127,124,-122,117,-113,105,-99,89,-81,70,-60,48,-37,24,-13,0,12,-25,36,-49,59,-71,80,-90,98,-106,112,-118,121,-125,126,-127,126,-125,121,-118,112,-106,98,-90,80,-71,59,-49,36,-25,12,0,-13,24,-37,48,-60,70,-81,89,-99,105,-113,117,-122,124,-127},
{127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127,127,-127}
};

// ImX coefficients for 32p-DFT - size (N/2+1)*N bytes
prog_int8_t IMx_cons[DFT_Nb2][DFT_N] PROGMEM={
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,-13,-25,-37,-49,-60,-71,-81,-90,-99,-106,-113,-118,-122,-125,-127,-127,-127,-125,-122,-118,-113,-106,-99,-90,-81,-71,-60,-49,-37,-25,-13,0,12,24,36,48,59,70,80,89,98,105,112,117,121,124,126,127,126,124,121,117,112,105,98,89,80,70,59,48,36,24,12},
{0,-25,-49,-71,-90,-106,-118,-125,-127,-125,-118,-106,-90,-71,-49,-25,0,24,48,70,89,105,117,124,127,124,117,105,89,70,48,24,0,-25,-49,-71,-90,-106,-118,-125,-127,-125,-118,-106,-90,-71,-49,-25,0,24,48,70,89,105,117,124,127,124,117,105,89,70,48,24},
{0,-37,-71,-99,-118,-127,-125,-113,-90,-60,-25,12,48,80,105,121,127,121,105,80,48,12,-25,-60,-90,-113,-125,-127,-118,-99,-71,-37,0,36,70,98,117,126,124,112,89,59,24,-13,-49,-81,-106,-122,-127,-122,-106,-81,-49,-13,24,59,89,112,124,126,117,98,70,36},
{0,-49,-90,-118,-127,-118,-90,-49,0,48,89,117,127,117,89,48,0,-49,-90,-118,-127,-118,-90,-49,0,48,89,117,127,117,89,48,0,-49,-90,-118,-127,-118,-90,-49,0,48,89,117,127,117,89,48,0,-49,-90,-118,-127,-118,-90,-49,0,48,89,117,127,117,89,48},
{0,-60,-106,-127,-118,-81,-25,36,89,121,124,98,48,-13,-71,-113,-127,-113,-71,-13,48,98,124,121,89,36,-25,-81,-118,-127,-106,-60,0,59,105,126,117,80,24,-37,-90,-122,-125,-99,-49,12,70,112,127,112,70,12,-49,-99,-125,-122,-90,-37,24,80,117,126,105,59},
{0,-71,-118,-125,-90,-25,48,105,127,105,48,-25,-90,-125,-118,-71,0,70,117,124,89,24,-49,-106,-127,-106,-49,24,89,124,117,70,0,-71,-118,-125,-90,-25,48,105,127,105,48,-25,-90,-125,-118,-71,0,70,117,124,89,24,-49,-106,-127,-106,-49,24,89,124,117,70},
{0,-81,-125,-113,-49,36,105,126,89,12,-71,-122,-118,-60,24,98,127,98,24,-60,-118,-122,-71,12,89,126,105,36,-49,-113,-125,-81,0,80,124,112,48,-37,-106,-127,-90,-13,70,121,117,59,-25,-99,-127,-99,-25,59,117,121,70,-13,-90,-127,-106,-37,48,112,124,80},
{0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89,0,-90,-127,-90,0,89,127,89},
{0,-99,-125,-60,48,121,105,12,-90,-127,-71,36,117,112,24,-81,-127,-81,24,112,117,36,-71,-127,-90,12,105,121,48,-60,-125,-99,0,98,124,59,-49,-122,-106,-13,89,126,70,-37,-118,-113,-25,80,127,80,-25,-113,-118,-37,70,126,89,-13,-106,-122,-49,59,124,98},
{0,-106,-118,-25,89,124,48,-71,-127,-71,48,124,89,-25,-118,-106,0,105,117,24,-90,-125,-49,70,127,70,-49,-125,-90,24,117,105,0,-106,-118,-25,89,124,48,-71,-127,-71,48,124,89,-25,-118,-106,0,105,117,24,-90,-125,-49,70,127,70,-49,-125,-90,24,117,105},
{0,-113,-106,12,117,98,-25,-122,-90,36,124,80,-49,-127,-71,59,127,59,-71,-127,-49,80,124,36,-90,-122,-25,98,117,12,-106,-113,0,112,105,-13,-118,-99,24,121,89,-37,-125,-81,48,126,70,-60,-127,-60,70,126,48,-81,-125,-37,89,121,24,-99,-118,-13,105,112},
{0,-118,-90,48,127,48,-90,-118,0,117,89,-49,-127,-49,89,117,0,-118,-90,48,127,48,-90,-118,0,117,89,-49,-127,-49,89,117,0,-118,-90,48,127,48,-90,-118,0,117,89,-49,-127,-49,89,117,0,-118,-90,48,127,48,-90,-118,0,117,89,-49,-127,-49,89,117},
{0,-122,-71,80,117,-13,-125,-60,89,112,-25,-127,-49,98,105,-37,-127,-37,105,98,-49,-127,-25,112,89,-60,-125,-13,117,80,-71,-122,0,121,70,-81,-118,12,124,59,-90,-113,24,126,48,-99,-106,36,127,36,-106,-99,48,126,24,-113,-90,59,124,12,-118,-81,70,121},
{0,-125,-49,105,89,-71,-118,24,127,24,-118,-71,89,105,-49,-125,0,124,48,-106,-90,70,117,-25,-127,-25,117,70,-90,-106,48,124,0,-125,-49,105,89,-71,-118,24,127,24,-118,-71,89,105,-49,-125,0,124,48,-106,-90,70,117,-25,-127,-25,117,70,-90,-106,48,124},
{0,-127,-25,121,48,-113,-71,98,89,-81,-106,59,117,-37,-125,12,127,12,-125,-37,117,59,-106,-81,89,98,-71,-113,48,121,-25,-127,0,126,24,-122,-49,112,70,-99,-90,80,105,-60,-118,36,124,-13,-127,-13,124,36,-118,-60,105,80,-90,-99,70,112,-49,-122,24,126},
{0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127,0,-127,0,127},
{0,-127,24,121,-49,-113,70,98,-90,-81,105,59,-118,-37,124,12,-127,12,124,-37,-118,59,105,-81,-90,98,70,-113,-49,121,24,-127,0,126,-25,-122,48,112,-71,-99,89,80,-106,-60,117,36,-125,-13,127,-13,-125,36,117,-60,-106,80,89,-99,-71,112,48,-122,-25,126},
{0,-125,48,105,-90,-71,117,24,-127,24,117,-71,-90,105,48,-125,0,124,-49,-106,89,70,-118,-25,127,-25,-118,70,89,-106,-49,124,0,-125,48,105,-90,-71,117,24,-127,24,117,-71,-90,105,48,-125,0,124,-49,-106,89,70,-118,-25,127,-25,-118,70,89,-106,-49,124},
{0,-122,70,80,-118,-13,124,-60,-90,112,24,-127,48,98,-106,-37,127,-37,-106,98,48,-127,24,112,-90,-60,124,-13,-118,80,70,-122,0,121,-71,-81,117,12,-125,59,89,-113,-25,126,-49,-99,105,36,-127,36,105,-99,-49,126,-25,-113,89,59,-125,12,117,-81,-71,121},
{0,-118,89,48,-127,48,89,-118,0,117,-90,-49,127,-49,-90,117,0,-118,89,48,-127,48,89,-118,0,117,-90,-49,127,-49,-90,117,0,-118,89,48,-127,48,89,-118,0,117,-90,-49,127,-49,-90,117,0,-118,89,48,-127,48,89,-118,0,117,-90,-49,127,-49,-90,117},
{0,-113,105,12,-118,98,24,-122,89,36,-125,80,48,-127,70,59,-127,59,70,-127,48,80,-125,36,89,-122,24,98,-118,12,105,-113,0,112,-106,-13,117,-99,-25,121,-90,-37,124,-81,-49,126,-71,-60,127,-60,-71,126,-49,-81,124,-37,-90,121,-25,-99,117,-13,-106,112},
{0,-106,117,-25,-90,124,-49,-71,127,-71,-49,124,-90,-25,117,-106,0,105,-118,24,89,-125,48,70,-127,70,48,-125,89,24,-118,105,0,-106,117,-25,-90,124,-49,-71,127,-71,-49,124,-90,-25,117,-106,0,105,-118,24,89,-125,48,70,-127,70,48,-125,89,24,-118,105},
{0,-99,124,-60,-49,121,-106,12,89,-127,70,36,-118,112,-25,-81,127,-81,-25,112,-118,36,70,-127,89,12,-106,121,-49,-60,124,-99,0,98,-125,59,48,-122,105,-13,-90,126,-71,-37,117,-113,24,80,-127,80,24,-113,117,-37,-71,126,-90,-13,105,-122,48,59,-125,98},
{0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89,0,-90,127,-90,0,89,-127,89},
{0,-81,124,-113,48,36,-106,126,-90,12,70,-122,117,-60,-25,98,-127,98,-25,-60,117,-122,70,12,-90,126,-106,36,48,-113,124,-81,0,80,-125,112,-49,-37,105,-127,89,-13,-71,121,-118,59,24,-99,127,-99,24,59,-118,121,-71,-13,89,-127,105,-37,-49,112,-125,80},
{0,-71,117,-125,89,-25,-49,105,-127,105,-49,-25,89,-125,117,-71,0,70,-118,124,-90,24,48,-106,127,-106,48,24,-90,124,-118,70,0,-71,117,-125,89,-25,-49,105,-127,105,-49,-25,89,-125,117,-71,0,70,-118,124,-90,24,48,-106,127,-106,48,24,-90,124,-118,70},
{0,-60,105,-127,117,-81,24,36,-90,121,-125,98,-49,-13,70,-113,127,-113,70,-13,-49,98,-125,121,-90,36,24,-81,117,-127,105,-60,0,59,-106,126,-118,80,-25,-37,89,-122,124,-99,48,12,-71,112,-127,112,-71,12,48,-99,124,-122,89,-37,-25,80,-118,126,-106,59},
{0,-49,89,-118,127,-118,89,-49,0,48,-90,117,-127,117,-90,48,0,-49,89,-118,127,-118,89,-49,0,48,-90,117,-127,117,-90,48,0,-49,89,-118,127,-118,89,-49,0,48,-90,117,-127,117,-90,48,0,-49,89,-118,127,-118,89,-49,0,48,-90,117,-127,117,-90,48},
{0,-37,70,-99,117,-127,124,-113,89,-60,24,12,-49,80,-106,121,-127,121,-106,80,-49,12,24,-60,89,-113,124,-127,117,-99,70,-37,0,36,-71,98,-118,126,-125,112,-90,59,-25,-13,48,-81,105,-122,127,-122,105,-81,48,-13,-25,59,-90,112,-125,126,-118,98,-71,36},
{0,-25,48,-71,89,-106,117,-125,127,-125,117,-106,89,-71,48,-25,0,24,-49,70,-90,105,-118,124,-127,124,-118,105,-90,70,-49,24,0,-25,48,-71,89,-106,117,-125,127,-125,117,-106,89,-71,48,-25,0,24,-49,70,-90,105,-118,124,-127,124,-118,105,-90,70,-49,24},
{0,-13,24,-37,48,-60,70,-81,89,-99,105,-113,117,-122,124,-127,127,-127,124,-122,117,-113,105,-99,89,-81,70,-60,48,-37,24,-13,0,12,-25,36,-49,59,-71,80,-90,98,-106,112,-118,121,-125,126,-127,126,-125,121,-118,112,-106,98,-90,80,-71,59,-49,36,-25,12},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

//Input signal
int8_t x[DFT_N]={51,55,58,61,64,67,70,73,76,79,82,84,87,90,92,95,
97,99,102,104,106,108,110,112,113,115,117,118,119,121,122,123,
124,124,125,126,126,126,127,127,127,127,127,127,126,126,125,
125,124,123,122,121,120,119,118,116,115,113,112,110,108,107,105,103};

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
int gg;
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

	"ldi r16, 33 \n"
	"mov r10, r16 \n"
	"ldi r16, 64 \n"
	"mov r11, r16 \n"
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
	"mov r16, r10 \n"  
	"kloop: \n"
		"clr r8 \n"
		"clr r9 \n"
		// reset x address
		"ldi R26, lo8(x) \n" 
		"ldi R27, hi8(x) \n" 

		// // Loop through N samples of x
		"mov R17, r11 \n" 
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
			"asr r1 \n"	// Overflow Gaurd + div by 2 (Also Magnitude Correction)
			"ror r0 \n"
			"asr r1 \n"	// Overflow Gaurd + div by 2 (Also Magnitude Correction)
			"ror r0 \n"
			"add R8, R0 \n"
			"adc R9, R1 \n"
			"dec R17 \n"
		"brne iloop \n"	
		// Discard the lower 8 bytes as we scale from 2e-15 to 2e-7 (aka x2e8)
		// store mac'd kth bin back
		// Final Magnitude Correction. Overall the whole thing must be divided by N/2. 
		"asr r9 \n"
		// special case if k=0 or k=N/2, then it has to be div by 2 again.
		"cp r16, r10 \n" 
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
	"mov r16, r10 \n" 
	"kkloop: \n"
		"clr r8 \n"
		"clr r9 \n"
		// reset x address
		"ldi R26, lo8(x) \n" 
		"ldi R27, hi8(x) \n" 

		// // Loop through N samples of x
		"mov R17, r11 \n"
		"iiloop: \n"
			// r20 <- [ImX_cons], Y++
			"ld R20, Y+ \n"
			// -1 * r20 , Becuase all ImX has to accumulated * -1
			"neg r20 \n"
			// r21 <- [x], X++
			"ld R21, X+ \n"
			// r9:8 = mac(r20*r21)
			"fmuls R20, R21 \n"
			"asr r1 \n" // Overflow Gaurd + div by 2 (Also Magnitude Correction)
			"ror r0 \n"
			"asr r1 \n"
			"ror r0 \n"
			"asr r1 \n"	
			"ror r0 \n"
			"asr r1 \n"	// Overflow Gaurd + div by 2 (Also Magnitude Correction)
			"ror r0 \n"
			"add R8, R0 \n"
			"adc R9, R1 \n"
			"dec R17 \n"
		"brne iiloop \n"
		// Discard the lower 8 bytes as we scale from 2e-15 to 2e-7 (aka x2e8)
		// store mac'd kth bin back
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
	"mov r17, r10 \n"		// main loop counter
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
		lcd_lvl[k]=dftX[k]>>3;

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