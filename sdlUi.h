#include <SDL/SDL.h>

#define WINDOW_W  1024
#define WINDOW_H  512
#define WHITE_COL 0xffffffff
#define RED_COL   0xffff0000
#define BLACK_COL 0

SDL_Event e;
Uint8 *keys;

static int c8_keymap[0x10] = { 
    SDLK_KP0, SDLK_KP1, SDLK_KP2, SDLK_KP3,
    SDLK_KP4, SDLK_KP5, SDLK_KP6, SDLK_KP7,
    SDLK_KP8, SDLK_KP9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f
};


void init_ui(int PW, int PH);
void draw_screen(unsigned char* screen);
void draw_screen_pause(unsigned char* screen);
void quit(int status);
