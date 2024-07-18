#include "emulator.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "display.h"

void init()
{
    memset(memory, 0, MEMORY_SIZE);
    for(int i = 0; i < NUMBER_OF_REGISTERS; i++)
    {
        Vs[i] = 0;
    }
    I = 0;
    for(int i = 0; i < STACK_SIZE; i++)
    {
        jumpstack[i] = 0;
    }
    jumpstack_pointer = 0;
    pc = FIRST_ADDRESS;
    
    init_display();
}

int load_rom(const char *path)
{
    FILE *fp = fopen(path, "rb");
    if(fp == NULL)
    {
        return -1;
    }
    fread(&memory[FIRST_ADDRESS], 1, (MEMORY_SIZE-FIRST_ADDRESS)*sizeof(uint8_t), fp);
    fclose(fp);
    return 0;
}


uint16_t get_opcode()
{
    //An instruction is two bytes, so we need to read two successive bytes from memory
    // and combine them into one 16-bit instruction
    uint8_t fh = memory[pc];
    uint8_t sh = memory[pc+1];
    return ((uint16_t)fh << 8) | sh; 
}

void decode_opcode(uint16_t opcode)
{
    uint8_t fh = (uint8_t)(opcode >> 8);
    uint8_t sh = (uint8_t)(opcode & 0xFF);
    switch(fh)
    {
        case 0x00:
            switch(sh)
            {
                case 0xE0:
                    clear_screen();
                    break;
                case 0xEE:
                    pc = jumpstack[jumpstack_pointer];
                    jumpstack_pointer--;
                    break;
                
            }
            break;
        
    }
}

void update_input()
{

}

void update()
{
    while(!WindowShouldClose())
    {
        update_input();
        BeginDrawing();
        update_display();
        EndDrawing();
    }
}



int main()
{
    init();
    //load_rom("roms/ibm.ch8");
    update();
}