#ifndef CHIP8_CPU
#define CHIP8_CPU

#include <stdint.h>
#include "display.h"

typedef uint8_t reg;

#define NUMBER_OF_REGISTERS 17
#define CARRY_REGISTER 0x0F


// first 512 bytes are reserved for the interpreter
// so free addresses goes to 0x200 (chip8*)=512) to 0xfff
// it's 3584 bytes
// 512 + 3584 = full memory size = 4096
#define FIRST_ADDRESS 512
#define USABLE_MEMORY 3584
#define MEMORY_SIZE (FIRST_ADDRESS+USABLE_MEMORY) 


#define STACK_SIZE 16



typedef struct chip8
{
    reg Vs[NUMBER_OF_REGISTERS-1];
    reg I;


    uint8_t memory[MEMORY_SIZE];
    // program counter (chip8*)points to where we are in the memory)
    // must be able to points in a range 0 -> 4095
    // 4095 = 1111 1111 1111 
    // so the smallest type that can represent it is uint16 
    uint16_t pc; 
    uint16_t pc;
        
    uint16_t jumpstack[STACK_SIZE];
    uint8_t jumpstack_pointer; 

} chip8;


typedef struct nibble
{
    uint8_t first_half;
    uint8_t kk;
    uint8_t first_number;
    uint8_t second_number;
    uint8_t n;
    uint16_t nnn;
    uint8_t x;
    uint8_t y;
} nibble;

// Déclarations des constantes
const uint8_t NA_FUNCTION = 0;
const uint8_t CLS = 1;
const uint8_t RET = 2;
const uint8_t JP = 3;
const uint8_t CALL = 4;
const uint8_t SE = 5;
const uint8_t SNE = 6;
const uint8_t SEV = 7;
const uint8_t LD = 8;
const uint8_t ADD = 9;
const uint8_t LDVY = 10;
const uint8_t OR = 11;
const uint8_t AND = 12;
const uint8_t XOR = 13;
const uint8_t ADDVY = 14;
const uint8_t SUBVY = 15;
const uint8_t SHR = 16;
const uint8_t SUBN = 17;
const uint8_t SHL = 18;
const uint8_t SNEV = 19;
const uint8_t LDI = 20;
const uint8_t JPV0 = 21;
const uint8_t RND = 22;
const uint8_t DRAW = 23;
const uint8_t SKP = 24;
const uint8_t SKNP = 25;
const uint8_t LD_DT_VX = 26;
const uint8_t LD_KEY = 27;
const uint8_t LD_DT = 28;
const uint8_t LD_ST = 29;
const uint8_t ADD_I = 30;
const uint8_t LD_F = 31;
const uint8_t LD_B = 32;
const uint8_t LD_I_VX = 33;
const uint8_t LD_VX_I = 34;


nibble decode_opcode(uint16_t opcode);

void nib_to_func(nibble nib, chip8* ch);

// Déclarations des fonctions
void undef(chip8*, nibble);
void cls(chip8*, nibble);
void ret(chip8*, nibble);
void jp(chip8*, nibble);
void call(chip8*, nibble);
void se(chip8*, nibble);
void sne(chip8*, nibble);
void sev(chip8*, nibble);
void ld(chip8*, nibble);
void add(chip8*, nibble);
void ldvy(chip8*, nibble);
void or_op(chip8*, nibble);
void and_op(chip8*, nibble);
void xor_op(chip8*, nibble);
void addvy(chip8*, nibble);
void subvy(chip8*, nibble);
void shr(chip8*, nibble);
void subn(chip8*, nibble);
void shl(chip8*, nibble);
void snev(chip8*, nibble);
void ldi(chip8*, nibble);
void jpv0(chip8*, nibble);
void rnd(chip8*, nibble);
void draw(chip8*, nibble);
void skp(chip8*, nibble);
void sknp(chip8*, nibble);
void ld_dt_vx(chip8*, nibble);
void ld_key(chip8*, nibble);
void ld_dt(chip8*, nibble);
void ld_st(chip8*, nibble);
void add_i(chip8*, nibble);
void ld_f(chip8*, nibble);
void ld_b(chip8*, nibble);
void ld_i_vx(chip8*, nibble);
void ld_vx_i(chip8*, nibble);

// Tableau de pointeurs de fonctions
void (*function_table[])(chip8*, nibble) = {
    undef,       // NA_FUNCTION = 0
    cls,         // CLS = 1
    ret,         // RET = 2
    jp,          // JP = 3
    call,        // CALL = 4
    se,          // SE = 5
    sne,         // SNE = 6
    sev,         // SEV = 7
    ld,          // LD = 8
    add,         // ADD = 9
    ldvy,        // LDVY = 10
    or_op,       // OR = 11
    and_op,      // AND = 12
    xor_op,      // XOR = 13
    addvy,       // ADDVY = 14
    subvy,       // SUBVY = 15
    shr,         // SHR = 16
    subn,        // SUBN = 17
    shl,         // SHL = 18
    snev,        // SNEV = 19
    ldi,         // LDI = 20
    jpv0,        // JPV0 = 21
    rnd,         // RND = 22
    draw,        // DRAW = 23
    skp,         // SKP = 24
    sknp,        // SKNP = 25
    ld_dt_vx,    // LD_DT_VX = 26
    ld_key,      // LD_KEY = 27
    ld_dt,       // LD_DT = 28
    ld_st,       // LD_ST = 29
    add_i,       // ADD_I = 30
    ld_f,        // LD_F = 31
    ld_b,        // LD_B = 32
    ld_i_vx,     // LD_I_VX = 33
    ld_vx_i      // LD_VX_I = 34
};


void init_chip8(chip8* chip);
nibble get_opcode(chip8* chip);



#endif