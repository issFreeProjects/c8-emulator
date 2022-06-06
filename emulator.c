#include <stdio.h>
#include <sdlUi.h>


void smokeT()
{
  for(int i=0; i<64*32; i++)
    if(i%3==0 || (64*32-i)%3==0)
      draw_sq(i/32,i%64);
  w();
}


int main(int argc, char** argv)
{
  printf("Welcome to c8 emulator :)\n");
  init_ui();
  smokeT();
  return 0;
}
