#ifndef CHIP8_DISPLAY
#define CHIP8_DISPLAY

#include <stdint.h>
#include <raylib.h>

#define WIDTH_IN_PIXEL 64
#define HEIGHT_IN_PIXEL 32
#define SCALE_FACTOR 16

#define DISPLAY_WIDTH (WIDTH_IN_PIXEL*SCALE_FACTOR)
#define DISPLAY_HEIGHT (HEIGHT_IN_PIXEL*SCALE_FACTOR)


typedef enum pixelstate
{
    off = 0,
    on = 1
} pixelstate;

extern pixelstate screen[WIDTH_IN_PIXEL][HEIGHT_IN_PIXEL];

void init_display();
void clear_screen();
void deinit_display();
void update_display();





/*

#define FONT_WIDE 4
#define FONT_HEIGHT 5


typedef pixelstate font_character[FONT_HEIGHT][FONT_WIDE];

const font_character zero_char = {{on, on, on, on}, {on, off, off, on}, {on, off, off, on}, {on, off, off, on}, {on, on, on, on}};
const font_character one_char = {{off, off, on, off}, {off, on, on, off}, {on, off, on, off}, {off, off, on, off}, {off, off, on, off}};
const font_character two_char = {{on, on, on, off}, {on, off, on, off}, {off, off, on, off}, {off, on, off, off}, {on, on, on, on}};
const font_character three_char = {{on, on, on, on}, {off, off, off, on}, {off, on, on, on}, {off, off, off, on}, {on, on, on, on}};
const font_character four_char = {{off, on, off, off}, {off, on, off, off}, {on, on, on, off}, {off, off, on, off}, {off, off, on, off}};
const font_character five_char = {{on, on, on, on}, {on, off, off, off}, {on, on, on, on}, {off, off, off, on}, {on, on,on,on}};
const font_character six_char = {{off, off, on, off}, {off, on, off, off}, {on, on, on, on}, {on, off, off, on}, {on, on, on, on}};
const font_character seven_char = {{on, on, on, off}, {off, off, on, off}, {off, on, on, on}, {off, off, on, off}, {off, off, on, off}};
const font_character eight_char = {{off, on,on, off}, {on, off, off, on}, {off, on, on, off}, {on, off, off, on}, {off, on, on,off}};
const font_character nine_char = {{on, on, on, on}, {on, off, off, on}, {on, off, off, on}, {off, off, off, on}, {on, on, on, on}};

const font_character A_char = {{off, on, on, off}, {on, off, off, on}, {on, on, on, on}, {on, off, off, on}, {on, off, off, on}};
const font_character B_char = {{on, on, on, off}, {on, off, on, off}, {on, on, on, off}, {on, off, on, off}, {on, on, on, off}};
const font_character C_char = {{off, on, on, on}, {on, off, off, off}, {on, off, off, off}, {on, off, off, off}, {off, on, on, on}};
const font_character D_char = {{on, on, on, off}, {on, off, off, on}, {on, off, off, on}, {on, off, off, on}, {on, on, on, off}};
const font_character E_char = {{on, on, on, on}, {on, off, off, off}, {on, on, on, off}, {on, off, off, off}, {on, on, on, on}};
const font_character F_char = {{on, on, on, on}, {on, off, off, off}, {on, on, on, off}, {on, off, off, off}, {on, off, off, off}};
*/

#endif