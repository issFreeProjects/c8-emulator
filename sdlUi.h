#include <SDL/SDL.h>

#define WINDOW_W  1024
#define WINDOW_H  512
#define WHITE_COL 0xffffffff
#define BLACK_COL 0

SDL_Event e;
Uint8 *keys;

void handel_events();
void init_ui();
void draw_screen(unsigned char* screen, int W, int H);
void quit(int status);
