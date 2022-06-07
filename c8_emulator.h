#define mem_s  4096
#define pmem_s 16
#define sc_s   64*32
#define row_n  32
#define col_n  64
#define ni     ch8->pc += 2

unsigned char screen[sc_s];

typedef struct chip8{
  unsigned char memory[mem_s];
  unsigned char  V[pmem_s], Key[pmem_s], stack[pmem_s];
  unsigned short I, pc, sp; 
  unsigned char  delay_timer, sound_timer;
} C8; 



void c8_clear_mem(C8 *c8);
void c8_read_rom_to_mem(C8 *c8, char* path);
void c8_execH(unsigned short opcode, C8 *c8);
void c8_exec(C8 *c8);
void c8_sdl_main_loop(C8 *c8, unsigned char *screen);
void c8_init(char* path);
