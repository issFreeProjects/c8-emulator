#include <SDL2/SDL.h>
#include <sdlUi.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Event e;


int init_ui()
{
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
    window = SDL_CreateWindow(
        "chip8 emulator",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        WINDOW_W, WINDOW_H,                // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    surface = SDL_CreateRGBSurface(0, WINDOW_W, WINDOW_H, 32, 0, 0, 0, 0);
    if(!renderer) {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    mk_black_screen();
    return 0;
}


void draw_sq(int i, int j)
{
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_Rect r;
    r.x = WINDOW_W/64*(i%64);
    r.y = WINDOW_H/32*(j%32);
    r.w = WINDOW_W/64;
    r.h = WINDOW_H/32;
    SDL_RenderFillRect( renderer, &r );
    SDL_RenderPresent(renderer);
}

void mk_black_screen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

}


int w()
{
    while(1) { // SDL loop
      while( SDL_PollEvent( &e ) != 0 ) {
        if( e.type == SDL_QUIT ) {
          quit();
          return 0;
        }
      } // end of handling event.
    }
}


void quit()
{
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
}
