#include <sdlUi.h>


void init_ui()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(
            WINDOW_W, WINDOW_H,
            32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    keys = SDL_GetKeyState(NULL);
}


void draw_screen(unsigned char* screen, int pix_W, int pix_H)
{
    int x, y, i, j;
    SDL_Surface *surface = SDL_GetVideoSurface();
    SDL_LockSurface(surface);
    Uint32 *pixels = (Uint32 *)surface->pixels;

    for (x=0; x<WINDOW_W; x++)
        for(y=0; y<WINDOW_H; y++)
        {
            i = x/(WINDOW_W/pix_W);
            j = y/(WINDOW_H/pix_H);
            pixels[x+y*WINDOW_W] = screen[i+j*pix_W] ? WHITE_COL: BLACK_COL;
        }
    SDL_UnlockSurface(surface);
    SDL_Flip(surface);
}


void quit(int status)
{
    SDL_Quit();
    exit(status);
}
