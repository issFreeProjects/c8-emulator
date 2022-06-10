#include <sdlUi.h>

int pix_W, pix_H;


void init_ui(int PW, int PH)
{
    pix_W = PW; pix_H = PH;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(
            WINDOW_W, WINDOW_H,
            32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    keys = SDL_GetKeyState(NULL);
}


void draw_screenH(unsigned char* screen, int bg_color, int fg_color)
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
            pixels[x+y*WINDOW_W] = screen[i+j*pix_W] ? fg_color : bg_color;
        }
    SDL_UnlockSurface(surface);
    SDL_Flip(surface);
}


void draw_screen(unsigned char* screen)
{
    draw_screenH(screen, BLACK_COL, WHITE_COL);
}


void draw_screen_pause(unsigned char* screen)
{
    draw_screenH(screen, BLACK_COL, RED_COL);
}


void quit(int status)
{
    SDL_Quit();
    exit(status);
}
