#include <sdlUi.h>


void handel_events()
{
    SDL_PollEvent (&e);
    switch(e.type){
        case SDL_QUIT:
            quit(0);
    }
    if(keys[SDLK_p]){
        while(1){
            SDL_WaitEvent(&e);
            keys = SDL_GetKeyState(NULL);
            if(keys[SDLK_ESCAPE] || keys[SDLK_q] || e.type==SDL_QUIT)
                quit(0);
            if(keys[SDLK_u] || keys[SDLK_p])
                break;
        }
    }
}


void init_ui()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(
            WINDOW_W, WINDOW_H,
            32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    keys = SDL_GetKeyState(NULL);
}


void draw_screen(unsigned char* screen, int W, int H)
{
    int x, y, i, j;
    SDL_Surface *surface = SDL_GetVideoSurface();
    SDL_LockSurface(surface);
    Uint32 *pixels = (Uint32 *)surface->pixels;
    for (x=0; x<WINDOW_W; x++)
        for(y=0; y<WINDOW_H; y++){
            i = x/(WINDOW_W/W);
            j = y/(WINDOW_H/H);
            pixels[x+y*WINDOW_W] = screen[i+j*W] ? WHITE_COL: BLACK_COL;
        }
    SDL_UnlockSurface(surface);
    SDL_Flip(surface);
}


void quit(int status)
{
    SDL_Quit();
    exit(status);
}
