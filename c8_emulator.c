#include <stdio.h>
#include <sdlUi.h>
#include <string.h>
#include <stdlib.h>
#include <c8_emulator.h>

C8 c8;

void handel_events()
{
    SDL_PollEvent (&e);
    keys = SDL_GetKeyState(NULL);
    if(keys[SDLK_ESCAPE] || keys[SDLK_q] || e.type==SDL_QUIT)
        quit(0);
    if(keys[SDLK_r]){
       // reset* the cpu
       c8_clear_mem();
       c8_load_rom(&c8);
       c8_load_fonts(&c8);
    }if(keys[SDLK_p]){
        draw_screen_pause(screen);
        while(1){
            SDL_WaitEvent(&e);
            keys = SDL_GetKeyState(NULL);
            if(keys[SDLK_ESCAPE] || keys[SDLK_q] || e.type==SDL_QUIT){
                quit(0);
            }if(keys[SDLK_u] || keys[SDLK_p]){
                draw_screen(screen);
                break;
            }
        }
    }
}


void c8_clear_mem(){
      memset(c8.memory, 0, mem_s );
      memset(c8.V,      0, pmem_s);
      memset(c8.Key,    0, pmem_s);
      memset(c8.stack,  0, pmem_s);
      memset(screen,    0, sc_s  );

      c8.pc = 512;
      c8.sp = 0;   
}


void c8_load_rom(C8 *c8)
{
    FILE *f = fopen(c8->rom_path, "rb");
    if(!f){
      printf("file not found!");
      exit(1);
    }

    fread(c8->memory+512, 1, mem_s-512, f);
    fclose(f);
}


void chip8_timers(C8 * c8){
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
  int x, y, n, i, tmp;
    switch((opcode&0xF000)>>12){  // switch on first byte
      case 0x0:                                             // 0x0***
        switch(opcode&0x0FFF){
            case 0:
              c8->pc += 2;
              break;
            case 0xee:
              c8->pc = c8->stack[(--c8->sp)&0xf] + 0x2;
              break;
            case 0xe0:
              memset(screen, 0, sc_s);
              draw_screen(screen);
              c8->pc += 2;
              break;
        }
        break;
      case 0x1:                                             // 0x1***
        c8->pc = opcode&0x0fff;
        break;
      case 0x2:                                             // 0x2***
        c8->stack[(c8->sp++)&0xf] = c8->pc;
        c8->pc = opcode&0x0fff;
        break;
      case 0x3:                                             // 0x3***
          tmp = c8->V[(opcode&0xf00)>>8] - opcode&0xff;
          if(tmp==0){
            c8->pc += 4;
          }else c8->pc += 2;
          break;
      case 0x4:                                             // 0x4***
          y = c8->V[(opcode&0xf00)>>8] - opcode&0xff0>>4;
          if(y!=0)
            c8->pc += 4;
          else c8->pc += 2;
        break;
      case 0x5:                                             // 0x5***
        x = (opcode&0xf00)>>8;
        y = (opcode&0xf0)>>4;
        tmp = c8->V[x] - c8->V[y];
        if(tmp==0) c8->pc += 4;
        else c8->pc += 2;
        break;
      case 0x6:                                             // 0x6***
        c8->V[(opcode&0xf00)>>8] = opcode&0xff;
        c8->pc += 2;
        break;
      case 0x7:                                             // 0x7***
        c8->V[(opcode&0xf00)>>8] += opcode&0xff;
        c8->pc += 2;
        break;
      case 0x8:                                             // 0x8***
        x = (opcode&0x0f00)>>8;
        y = (opcode&0x00f0)>>4;
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
            tmp = (int)(c8->V[x]) + (int)(c8->V[y]);
            if(tmp < 256)
              c8->V[0xf] &= 0;
            else c8->V[0xf] = 1;
            c8->V[x] += c8->V[y];
            break;
          case 0x5:
            tmp = (int)(c8->V[x]) - (int)(c8->V[y]);
            if(tmp<0)
              c8->V[0xf] &= 0;
            else c8->V[0xf] = 1;
            c8->V[x] -= c8->V[y];
            break;
          case 0x6:
            c8->V[0xf] = (c8->V[x])&7;
            c8->V[x] = (c8->V[x])>>1;
            break;
          case 0x7:
            tmp = (int)(c8->V[x]) - (int)(c8->V[y]);
            if(tmp>0)
              c8->V[0xf] = 1;
            else c8->V[0xf] &= 0;
            c8->V[x] = c8->V[y] - c8->V[x];
            break;
          case 0xe:
            c8->V[0xf] = (c8->V[x])>>7;
            c8->V[x] = (c8->V[x])<<1;
            break;
        }
        c8->pc += 2;
        break;
      case 0x9:                                           // 0x9***
        x = (opcode&0xf00)>>8;
        y = (opcode&0xf0)>>4;
        tmp = c8->V[x] - c8->V[y];
        if(tmp!=0)
             c8->pc += 4;
        else c8->pc += 2;
        break;
      case 0xa:                                           // 0xa***
        c8->I  = opcode&0xfff;
        c8->pc += 2;
        break;
      case 0xb:                                           // 0xb***
        c8->pc = opcode&0xfff + c8->V[0];
        break;
      case 0xc:                                           // 0xc***
        c8->V[(opcode&0x0f00)>>8] = rand()&(opcode&0xff);
        c8->pc += 2;
        break;
      case 0xd:                                           // 0xd***
        x = c8->V[(opcode&0x0f00)>>8];
        y = c8->V[(opcode&0x00f0)>>4];
        n = opcode&0xf;
        c8->V[0xf] &= 0;
        for(int i=0; i<n; i++){
            pixel = c8->memory[c8->I + i];
            for(int j=0; j<8; j++){
                tmp = (x+j + (y+i)*64); 
                if(pixel & (0x80>>j)){
                  if(screen[tmp])
                    c8->V[0xf] = 1;
                  screen[tmp] ^= 1;
                }
            }
        }
        draw_screen(screen);
        c8->pc += 2;
        break;
      case 0xe:                                           // 0xe***
        keys = SDL_GetKeyState(NULL);
        x = (opcode&0xf00)>>8;
        switch(opcode&0xff){
          case 0x9e:
            if(keys[c8_keymap[c8->V[x]]])
                c8->pc += 4;
            else c8->pc += 2;
            break;
          case 0xa1:
            if(!keys[c8_keymap[c8->V[x]]])
                c8->pc += 4;
            else c8->pc += 2;
            break;
        }
        break;
      case 0xf:                                           // 0xf***
        x = (opcode&0xf00)>>8;
        switch(opcode&0xff){
          case 0x7:
            c8->V[x] = c8->delay_timer;
            c8->pc += 2;
            break;
          case 0xa:
            keys = SDL_GetKeyState(NULL);
            for(i=0; i<0x10; i++)
              if(keys[c8_keymap[i]]){
                c8->V[x] = i;
                c8->pc += 2;
              }
            break;
          case 0x15:
            c8->delay_timer = c8->V[x];
            c8->pc += 2;
            break;
          case 0x18:
            c8->sound_timer = c8->V[x];
            c8->pc += 2;
            break;
          case 0x1e:
            c8->I += c8->V[x];
            c8->pc += 2;
            break;
          case 0x29:
            c8->I = c8->V[x]*5;
            c8->pc += 2;
            break;
          case 0x33:
            c8->memory[c8->I] = c8->V[x] / 100;
            c8->memory[c8->I+1] = (c8->V[x] / 10) % 10;
            c8->memory[c8->I+2] = c8->V[x] % 10;
            c8->pc += 2;
            break;
          case 0x55:
            for(i=0; i<=x; i++)
                c8->memory[c8->I+i] = c8->V[i];
            c8->pc += 2;
            break;
          case 0x65:
            for(i=0; i<=x; i++)
              c8->V[i] = c8->memory[c8->I+i];
            c8->pc += 2;
            break;
        }
        break;
    }
    chip8_timers(c8);
}


void c8_exec(C8 *c8)
{
    unsigned short opcode;
    opcode = c8->memory[c8->pc]<<8 | c8->memory[c8->pc+1];
    //printf("Executing %04X at %04X , I:%02X SP:%02X\n",
    //              opcode, c8->pc, c8->I, c8->sp);
      c8_execH(opcode, c8);
}


void c8_load_fonts(C8 *c8)
{
    for(int i=0; i<80; i++)
      c8->memory[i] = c8_fontset[i];
}


void c8_init(char* path)
{
    printf("Welcome to c8 emulator :)\n");
    init_ui(col_n, row_n);
    c8_clear_mem();
    c8.rom_path = path;
    c8_load_rom(&c8);
    c8_load_fonts(&c8);
    while(1){
        c8_exec(&c8);
        handel_events(keys);
    }
}
