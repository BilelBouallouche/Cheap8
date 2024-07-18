#include "display.h"

#include <string.h>


pixelstate screen[WIDTH_IN_PIXEL][HEIGHT_IN_PIXEL];


void init_display()
{
    InitWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "CHIP8 emulator");
    HideCursor();
    SetTargetFPS(60);
    clear_screen();
}

void clear_screen()
{
    memset(screen, 0, WIDTH_IN_PIXEL*HEIGHT_IN_PIXEL);
}

void update_display()
{
    ClearBackground(BLACK);
    for(int x = 0; x < WIDTH_IN_PIXEL; x++)
    {
        for(int y = 0; y < HEIGHT_IN_PIXEL; y++)
        {
            if(screen[x][y] == on)
            {
                DrawRectangle(x*SCALE_FACTOR, y*SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, WHITE);
            }
        }
    }
}

void deinit_display()
{
    clear_screen();
    CloseWindow();
}
