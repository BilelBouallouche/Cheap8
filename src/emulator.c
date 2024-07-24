#include "emulator.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "cpu.h"

void init()
{   
    chip = malloc(sizeof(chip8));
    init_chip8(&chip);
    init_display();
}

int load_rom(const char *path)
{
    FILE *fp = fopen(path, "rb");
    if(fp == NULL)
    {
        return -1;
    }
    fread(&(chip->memory[FIRST_ADDRESS]), 1, (MEMORY_SIZE-FIRST_ADDRESS)*sizeof(uint8_t), fp);
    fclose(fp);
    return 0;
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