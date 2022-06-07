#include <sdlUi.h>

Uint8 * keys;

void handel_events()
{
    SDL_PollEvent (&e);
    switch(e.type){
        case SDL_QUIT:
            exit(0);
    }
    if(keys[SDLK_p]){
            while(1){
            SDL_WaitEvent(&e);
            keys = SDL_GetKeyState(NULL);
            if(keys[SDLK_ESCAPE] || keys[SDLK_q] || e.type==SDL_QUIT)
                exit(1);
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


void draw_sq(unsigned char* screen)
{
    int x, y, i, j;
    SDL_Surface *surface = SDL_GetVideoSurface();
    SDL_LockSurface(surface);
    Uint32 *pixels = (Uint32 *)surface->pixels;
    for (x=0; x<WINDOW_W; x++)
        for(y=0; y<WINDOW_H; y++){
            i = x/(WINDOW_W/64);
            j = y/(WINDOW_H/32);
            pixels[x+y*WINDOW_W] = screen[i+j*64] ? 0xffffffff: 0;
        }
    SDL_UnlockSurface(surface);
    SDL_Flip(surface);
}


void quit()
{
    SDL_Quit();
}
