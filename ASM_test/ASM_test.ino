#define DEBUG 1
#ifdef DEBUG
  #define DEBUG_PRINT(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
#endif


uint8_t arr[8] = {0,1,2,3,4,5,6,7}; 

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  DEBUG_PRINT("Hello World!");
  DEBUG_PRINT("Before: ");
  for(int i=0;i<8;i++){DEBUG_PRINT(arr[i]);}
 asm volatile (
    "push r2 \n push r3 \n"
    "push r16 \n push r17 \n"
    
    "ldi r16,5 \n"
    "ldi r17,8 \n"
    "ldi r28,lo8(arr) \n"
    "ldi r29,hi8(arr) \n"
    
    "some: \n"     
    "ld r2,Y \n"
    "add r2,r16 \n"
    "st Y+,r2 \n"
    "dec r17 \n"
    "brne some \n"
    
    "pop r17 \n pop r16 \n"
    "pop r3 \n pop r2 \n"
  );
  DEBUG_PRINT("After: ");
  for(int i=0;i<8;i++){DEBUG_PRINT(arr[i]);}
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
