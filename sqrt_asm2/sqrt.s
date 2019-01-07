#include <avr/io.h>
.global a_number
.global Increment_a_Number
Increment_a_Number:
      push r16
      lds r16, a_number
      inc      r16
      sts      a_number, r16
      pop r16
      ret