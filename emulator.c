#include <stdio.h>
#include <sdlUi.h>
#include <string.h>
#include <stdlib.h>

#define mem_s  4096
#define pmem_s 16
#define sc_s   64*32
#define row_n  32
#define col_n  64

typedef struct chip8{
  unsigned short memory[mem_s];
  unsigned char  V[pmem_s], Key[pmem_s], stack[pmem_s];
  unsigned short I, pc, sp;
  unsigned char  delay_timer, sound_timer;
  unsigned char  screen[sc_s];
} C8;



void c8_clear_mem(C8 *c8){
    memset(c8->memory, 0, mem_s );
    memset(c8->V,      0, pmem_s);
    memset(c8->Key,    0, pmem_s);
    memset(c8->stack,  0, pmem_s);
    memset(c8->screen, 0, sc_s  );
    
    c8->pc = 512;
    c8->sp = 0;
}


void read_rom_to_mem(C8 *c8, char* path)
{
    FILE *f = fopen(path, "rb");
    if(!f){
      printf("file not found!");
      exit(1);
    }

    fread(c8->memory+512, 1, mem_s-512, f);
}


void c8_timers(C8 *c8){
    if(c8->delay_timer > 0)
        c8->delay_timer--;
    if(c8->sound_timer > 0)
        c8->sound_timer--;
    if(c8->sound_timer != 0)
        printf("%c", 7);
}


void c8_exec(C8 *c8)
{
    // todo
}


void c8_draw(C8 *c8)
{
    int i,j;
    for(int n=0; n<sc_s; n++){
      i = n/32;
      j = n%64;
      if((c8->screen)[i,j])
        draw_sq(i,j);
    }
}


void init_chip()
{
    C8 c8;
    c8_clear_mem(&c8);
    read_rom_to_mem(&c8, "./roms/IBM_logo.ch8");
    
    while(1){
        c8_exec(&c8);
        c8_draw(&c8);
        // c8_prec(...)
    }
}


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
  init_chip();
  //  smokeT();
  return 0;
}
