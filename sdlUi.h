#include <SDL/SDL.h>

#define WINDOW_W  1024
#define WINDOW_H  512
#define WHITE_COL 0xffffffff
#define BLACK_COL 0

SDL_Event e;
Uint8 *keys;

static int keymap[0x10] = { 
    SDLK_0, SDLK_1, SDLK_2, SDLK_3,
    SDLK_4, SDLK_5, SDLK_6, SDLK_7,
    SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f
};


void handel_events();
void init_ui();
void draw_screen(unsigned char* screen, int W, int H);
void quit(int status);
