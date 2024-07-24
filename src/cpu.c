#include "cpu.h"

#include <stdlib.h>


void init_chip8(chip8* chip)
{
    memset(chip->memory, 0, MEMORY_SIZE);
    for(int i = 0; i < NUMBER_OF_REGISTERS; i++)
    {
        chip->Vs[i] = 0;
    }
    chip->I = 0;
    for(int i = 0; i < STACK_SIZE; i++)
    {
        chip->jumpstack[i] = 0;
    }
    chip->jumpstack_pointer = 0;
    chip->pc = FIRST_ADDRESS;
    srand( time( NULL ) );
}


uint16_t get_opcode(chip8* chip)
{
    //An instruction is two bytes, so we need to read two successive bytes from memory
    // and combine them into one 16-bit instruction
    uint8_t fh = chip->memory[chip->pc];
    uint8_t sh = chip->memory[chip->pc+1];
    return ((uint16_t)fh << 8) | sh; 
}

nibble decode_opcode(uint16_t opcode)
{
    nibble nib;
    uint8_t fh, sh, first_num, second_num;
    fh = (uint8_t)(opcode >> 8);
    sh = (uint8_t)(opcode & 0xFF);
    nib.first_half = fh;
    nib.kk = sh;
    second_num = fh & 0x0F;
    first_num = (fh >> 4) & 0x0F;
    nib.first_number = first_num;
    nib.second_number = second_num;
    nib.nnn = ((uint16_t)(second_num << 8)) | sh;
    nib.x = (opcode >> 8) & 0xF;
    nib.y = (opcode >> 4) & 0xF;
    nib.n = opcode & 0xF;
    return nib;
 
}


void nib_to_func(nibble nib, chip8* chip)
{
    uint8_t func_to_execute = NA_FUNCTION;
    switch(nib.first_number)
    {
        case 0:
            if(nib.second_number != 0)
            {
                //This instruction is only used on the old computers on which Chip-8 was originally implemented. It is ignored by modern computer
                printf("useless opcode\n");
                func_to_execute = NA_FUNCTION;
            }
            else
            {
                switch(nib.kk)
                {
                    case 0xE0:
                        func_to_execute = CLS;
                    break;
                    case 0xEE: 
                        func_to_execute = RET;
                    break;
                }
            }
        break;
        case 1:
            func_to_execute = JP;
        break;
        case 2:
            func_to_execute = CALL;
        break;
        case 3:
            func_to_execute = SE;
        break;
        case 4:
            func_to_execute = SNE;
        break;
        case 5:
            func_to_execute = SEV;
            break;
        case 6:
            func_to_execute = LD;
            break;
        case 7:
            func_to_execute = ADD;
            break;
        default:
            func_to_execute = NA_FUNCTION;


    }
    function_table[func_to_execute](chip, nib);
}


void undef(chip8 *chip, nibble nib)
{
    printf("Unimplemented yet or useless\n");
}

void cls(chip8*, nibble)
{
    clear_screen();
}
void ret(chip8* chip, nibble nib)
{
    chip->pc = chip->jumpstack[chip->jumpstack_pointer];
    chip->jumpstack_pointer--;
}
void jp(chip8* chip, nibble nib)
{
    chip->pc = nib.nnn;
}
void call(chip8* chip, nibble nib)
{
    chip->jumpstack_pointer++;
    chip->jumpstack[chip->jumpstack_pointer] = chip->pc;
    chip->pc = nib.nnn; 
}

void se(chip8*chip, nibble nib)
{
    if(chip->Vs[nib.x] == nib.kk)
    {
        chip->pc += 2;
    }    
}

void sne(chip8*chip, nibble nib)
{
    if(chip->Vs[nib.x] != nib.kk)
    {
        chip->pc += 2;
    }    
}

void sev(chip8*chip, nibble nib)
{
    if(chip->Vs[nib.x] == chip->Vs[nib.y])
    {
        chip->pc += 2;
    }
}

void ld(chip8*chip, nibble nib)
{
    chip->Vs[nib.x] = nib.kk;
}

void add(chip8*chip, nibble nib)
{
    chip->Vs[nib.x] += nib.kk;
}

void ldvy(chip8* chip, nibble nib)
{
    chip->Vs[nib.x] = chip->Vs[nib.y];
}

void or_op(chip8* chip, nibble nib)
{
    chip->Vs[nib.x] |= chip->Vs[nib.y];
}

void and_op(chip8* chip, nibble nib)
{
    chip->Vs[nib.x] &= chip->Vs[nib.y];
}


void xor_op(chip8* chip, nibble nib)
{
    chip->Vs[nib.x] ^= chip->Vs[nib.y];
}

void addvy(chip8* chip, nibble nib)
{
    uint16_t res = chip->Vs[nib.x] + chip->Vs[nib.y];
    if(res > 255)
    {
        chip->Vs[CARRY_REGISTER] = 1;
    }
    chip->Vs[nib.x] = res&0xFF;
}

void subvy(chip8 *chip, nibble nib)
{
    if(chip->Vs[nib.x] > chip->Vs[nib.y])
    {
        chip->Vs[CARRY_REGISTER] = 1;
    }
    chip->Vs[nib.x] -= chip->Vs[nib.y];
}

void shr(chip8* chip, nibble nib)
{
    uint8_t lsb = chip->Vs[nib.x];
    if(lsb == 1)
    {
        chip->Vs[CARRY_REGISTER] = 1;
    }
    else
    {
        chip->Vs[CARRY_REGISTER] = 0;
    }
    chip->Vs[nib.x] *= 2;
}

void subn(chip8* chip, nibble nib)
{
    if(chip->Vs[nib.y] > chip->Vs[nib.x])
    {
        chip->Vs[CARRY_REGISTER] = 1;
    }
    chip->Vs[nib.x] = chip->Vs[nib.y] - chip->Vs[nib.x];
}

void shl(chip8* chip, nibble nib)
{
    uint8_t msb = (chip->Vs[nib.x] & 0x80) >> 7;
    if(msb == 1)
    {
        chip->Vs[CARRY_REGISTER] = 1;
    }
    else
    {
        chip->Vs[CARRY_REGISTER] = 0;
    }
    chip->Vs[nib.x] *= 2;
}

void snev(chip8* chip, nibble nib)
{
    if(chip->Vs[nib.x] != chip->Vs[nib.y])
    {
        chip->pc += 2;
    }
}

void ldi(chip8* chip, nibble nib)
{
    chip->I = nib.nnn;
}

void jpv0(chip8* chip, nibble nib)
{
    chip->pc = nib.nnn + chip->Vs[0];
}

void rnd(chip8* chip, nibble nib)
{
    chip->Vs[nib.x] = (rand() % 256) & nib.kk;
}

void draw(chip8* chip, nibble nib)
{
    /*
        need to think wtf does the instructions means
        undef for now
    */
   undef(chip, nib);
}

void skp(chip8* chip, nibble nib)
{
    /*
        undef for now, need to implement input first
    */
   undef(chip, nib);
}

void sknp(chip8* chip, nibble nib)
{
    /*
        undef for now, need to implement input first
    */
   undef(chip, nib);
}

void ld_dt_vx(chip8* chip, nibble nib)
{
    /*
        undef for now, need to implement timer first
    */
    undef(chip, nib);   
}
void ld_key(chip8* chip, nibble nib)
{
    /*
        undef for now, need to implement input first
    */
    undef(chip, nib);    
}
void ld_dt(chip8* chip, nibble nib)
{
    /*
        undef for now, need to implement timer first
    */
    undef(chip, nib); 
}
void ld_st(chip8* chip, nibble nib)
{
    /*
        undef for now, need to implement timer first
    */
    undef(chip, nib); 
}

void add_i(chip8* chip, nibble nib)
{
    chip->I += chip->Vs[nib.x];
}
void ld_f(chip8* chip, nibble nib)
{
    /*undef for now*/
    undef(chip, nib);
}
void ld_b(chip8* chip, nibble nib)
{
    uint8_t nb = chip->Vs[nib.x];
    chip->memory[chip->I] = nb / 100;
    chip->memory[chip->I + 1] = (nb/10)%10;
    chip->memory[chip->I + 2] = nb%10; 
}
void ld_i_vx(chip8* chip, nibble nib)
{
    for(int i = 0; i < nib.x; i++)
    {
        chip->memory[chip->I+i] = chip->Vs[i];
    }

}
void ld_vx_i(chip8* chip, nibble nib)
{
    for(int i = 0; i < nib.x; i++)
    {
        chip->Vs[i] = chip->memory[chip->I+i];
    }
}



void decode_opcode(uint16_t opcode)
{
    uint8_t fh = (uint8_t)(opcode >> 8);
    uint8_t sh = (uint8_t)(opcode & 0xFF);
    
    uint8_t shfh = fh & 0x0F;
    uint8_t fhfh = (fh >> 4) & 0x0F;
    if(fhfh == 0)
    {
        if(shfh != 0)
        {
            //This instruction is only used on the old computers on which Chip-8 was originally implemented. It is ignored by modern computer
            printf("useless opcode\n");
            return;
        }
        else
        {
            switch(sh)
            {
                case 0xE0:
                    clear_screen();
                    break;
                case 0xEE: // return from subroutine
                    // we set pc to the address on the top of the stack
                    pc = jumpstack[jumpstack_pointer];
                    jumpstack_pointer--;
                    break;
            }
        }
    }
    if(fhfh == 1)
    {
        uint16_t addr = (sh << 4) | shfh;
        pc = addr;
    }
    if(fhfh == 2)
    {
        uint16_t addr = (sh << 4) | shfh;
        jumpstack_pointer++;
        jumpstack[jumpstack_pointer] = pc;
        pc = addr; 
    }
    if(fhfh == 3)
    {
        if(Vs[shfh] == sh)
        {
            pc += 2;
        }
    }
    if(fhfh == 4)
    {
        if(Vs[shfh] != sh)
        {
            pc += 2;
        }
    }
    
    if(fhfh == 5)
    {
        uint8_t x = shfh;
        uint8_t y = (sh >> 4) & 0x0F;
        if(Vs[x] == Vs[y])
        {
            pc += 2;
        }
    }
    if(fhfh == 6)
    {
        uint8_t x = shfh;
        Vs[x] = sh;
    }
    if(fhfh == 7)
    {
        uint8_t x = shfh;
        Vs[x] += sh;
    }
    if(fhfh == 8)
    {

    }
    

}
*/

