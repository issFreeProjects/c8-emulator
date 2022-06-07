#include <SDL/SDL.h>

#define WINDOW_W 1024
#define WINDOW_H 512
#define WHITE_COL 255, 255, 255, 255
#define BLACK_COL 0  , 0  , 0  , 255

SDL_Event e;

void handel_events();
void init_ui();
void draw_sq(unsigned char* gr);
int w();
void quit();
