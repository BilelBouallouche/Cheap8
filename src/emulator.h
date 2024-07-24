#ifndef CHIP8_EMULATOR
#define CHIP8_EMULATOR

#include <stdint.h>



void init();
int load_rom(const char *path);
void update();

chip8* chip;





#endif