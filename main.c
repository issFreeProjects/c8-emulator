#include <stdio.h>
#include <stdlib.h>
#include "c8_emulator.h"

int main(int argc, char** argv)
{
    if(argc<2){
        printf("Use ./emulator path/to/rom.c8\n");
        exit(0);
    }else if(argc == 2)
        c8_init(argv[1]);
    
    return 0;
}

