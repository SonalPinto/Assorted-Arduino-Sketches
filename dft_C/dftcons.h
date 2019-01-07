#ifndef DFTCONS_H
#define DFTCONS_H

#define DFT_N 64
#define DFT_Nb2 33
#define LOG2_Nb2 5

//ReX coefficients for (64)pt-DFT
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

// ImX coefficients for (64)pt-DFT - size (N/2+1)*N bytes
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

// 64pt Hamming Window
prog_int8_t window[DFT_N] PROGMEM={10,10,11,13,15,17,20,24,28,32,37,42,47,53,58,64,70,76,82,87,93,98,103,107,111,115,
	118,121,123,125,126,127,127,126,125,123,121,118,115,111,107,103,98,93,87,82,76,70,64,58,53,47,42,37,32,28,24,20,17,15,13,11,10,10};

// 18*log2
prog_uint8_t logMag[128] PROGMEM={0,0,0,36,42,47,51,54,57,60,62,65,67,69,70,72,74,75,76,78,79,80,81,
	83,84,85,86,87,87,88,89,90,91,92,92,93,94,94,95,96,96,97,98,98,99,99,100,
	101,101,102,102,103,103,104,104,105,105,105,106,106,107,107,108,108,108,109,
	109,110,110,110,111,111,111,112,112,112,113,113,113,114,114,114,115,115,115,
	116,116,116,117,117,117,117,118,118,118,119,119,119,119,120,120,120,120,121,
	121,121,121,122,122,122,122,123,123,123,123,123,124,124,124,124,125,125,125,
	125,125,126,126,126
};

// Band selction for the 16 LCD columns
//uint8_t Bands[16]={1,2,3,4,5,6,7,8,9,10,12,15,19,24,30,32};
uint8_t Bands[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

#endif