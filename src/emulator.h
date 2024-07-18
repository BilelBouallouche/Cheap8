#ifndef CHIP8_EMULATOR
#define CHIP8_EMULATOR

#include <stdint.h>

typedef uint8_t reg;

#define NUMBER_OF_REGISTERS 17

reg Vs[NUMBER_OF_REGISTERS-1];
reg I;

// first 512 bytes are reserved for the interpreter
// so free addresses goes to 0x200 (=512) to 0xfff
// it's 3584 bytes
// 512 + 3584 = full memory size = 4096
#define FIRST_ADDRESS 512
#define USABLE_MEMORY 3584
#define MEMORY_SIZE (FIRST_ADDRESS+USABLE_MEMORY) 

uint8_t memory[MEMORY_SIZE];

// program counter (points to where we are in the memory)
// must be able to points in a range 0 -> 4095
// 4095 = 1111 1111 1111 
// so the smallest type that can represent it is uint16 
uint16_t pc; 

#define STACK_SIZE 16

uint16_t jumpstack[STACK_SIZE];
uint8_t jumpstack_pointer; 


void init();
int load_rom(const char *path);
void update();
#endif