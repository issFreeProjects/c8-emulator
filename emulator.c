#include <stdio.h>
#include <sdlUi.h>
#include <string.h>
#include <stdlib.h>

#define mem_s  4096
#define pmem_s 16
#define sc_s   64*32
#define row_n  32
#define col_n  64
#define ni     ch8->pc += 2

unsigned char screen[sc_s];
int times = 0;

typedef struct chip8{
  unsigned char memory[mem_s];
  unsigned char  V[pmem_s], Key[pmem_s], stack[pmem_s];
  unsigned short I, pc, sp;
  unsigned char  delay_timer, sound_timer;
} C8;



void c8_clear_mem(C8 *c8){
    memset(c8->memory, 0, mem_s );
    memset(c8->V,      0, pmem_s);
    memset(c8->Key,    0, pmem_s);
    memset(c8->stack,  0, pmem_s);
    memset(screen, 0, sc_s  );
    
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


void c8_execH(unsigned short opcode, C8 *c8)
{
  unsigned char pixel;
  int x, y, n;
    switch((opcode&0xF000)>>12){  // switch on first byte
      case 0x0:
        switch(opcode&0x0FFF){
            case 0xee:
              c8->pc = c8->stack[(--c8->sp)&0xF];
              c8->sp--;
            case 0xe0:
              memset(screen, 0, sc_s);
              c8->pc += 2;
        }
        break;
      case 0x1:
        c8->pc = opcode&0x0FFF;
        break;
      case 0x2:
        c8->stack[(c8->sp++)&0xf] = c8->pc;
        c8->pc                    = opcode&0x0FFF;
        break;
//      case 0x3:
//        break;
//      case 0x4:
//        break;
//      case 0x5:
//        break;
      case 0x6:
        c8->V[(opcode&0xf00)>>8]  = opcode&0xff;
        c8->pc += 2;
        break;
      case 0x7:
        c8->V[(opcode&0xf00)>>8] += opcode&0xff;
        c8->pc += 2;
        break;
      case 0x8:
        x = (opcode&0x0f00)>>8;
        y = (opcode&0x00f0)>>8;
        switch(opcode&0xf){
          case 0x0:
            c8->V[x]  = c8->V[y];
            break;
          case 0x1:
            c8->V[x] |= c8->V[y];
            break;
          case 0x2:
            c8->V[x] &= c8->V[y];
            break;
          case 0x3:
            c8->V[x] ^= c8->V[y];
            break;
          case 0x4:
            c8->V[x] += c8->V[y];
            if(c8->V[x] < 256)
              c8->V[0xf] &= 0;
            else c8->V[0xf] = 1;
            break;
          case 0x5:
            if(c8->V[x] > c8->V[y])
              c8->V[0xf] &= 0;
            else c8->V[0xf] = 1;
            c8->V[x] -= c8->V[y];
            break;
          case 0x6:
            if((c8->V[x])&0x1 == 1)
              c8->V[0xf] = 1;
            else c8->V[0xf] &= 0;
            c8->V[x] >> 1;
            break;
          case 0x7:
            if(c8->V[y] > c8->V[x])
              c8->V[0xf] = 1;
            else c8->V[0xf] &= 0;
            c8->V[x] = c8->V[y] - c8->V[x];
            break;
          case 0xe:
            c8->V[0xf] = c8->V[x] >> 7;
            (c8->V[x]) << 1;
            break;
        }
        c8->pc += 2;
        break;
      case 0x9:
        break;
      case 0xa:
        c8->I  = opcode&0xfff;
        c8->pc += 2;
        break;
      case 0xb:
        c8->pc = opcode&0xfff + c8->V[0];
        break;
      case 0xc:
        c8->V[(opcode&0x0f00)>>8] = (c8->I)&(opcode&0xff);
        c8->pc += 2;
        break;
      case 0xd:
        x = c8->V[(opcode&0x0f00)>>8];
        y = c8->V[(opcode&0x00f0)>>4];
        n = opcode&0xf;
        c8->V[0xf] &= 0;
        for(int i=0; i<n; i++){
            pixel = c8->memory[c8->I + i];
            for(int j=0; j<8; j++){
                if(pixel & (0x80>>j)){
                  if(screen[x+j + (y+i)*64])
                    c8->V[0xf] = 1;
                  screen[x+j + (y+i)*64] ^= 1;
                }
            }
        }
        c8->pc += 2;
        break;
      case 0xe:
        break;
    }
}


void c8_exec(C8 *c8)
{
    unsigned short opcode;
    opcode = c8->memory[c8->pc]<<8 | c8->memory[c8->pc+1];
    printf("%d exec %04X at PC %04X, I:%02X SP:%02X\n",
                  times, opcode, c8->pc, c8->I, c8->sp);
    c8_execH(opcode, c8);
    times++;
}


void sdl_main_loop(C8 *c8, unsigned char *screen)
{
    c8_exec(c8);
    draw_sq(screen);
}


int main(int argc, char** argv)
{
  C8 c8;
  printf("Welcome to c8 emulator :)\n");
  init_ui();
  c8_clear_mem(&c8);
  read_rom_to_mem(&c8, argv[1]);
  while(1){
    sdl_main_loop(&c8, screen);
    handel_events();
  }
  return 0;
}
