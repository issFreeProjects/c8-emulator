CC = "gcc"
BL = "build"

main:
	$(CC) -I . -c sdlUi.c -o $(BL)/sdlUi.o -lSDL2
	$(CC) -I . -c emulator.c -o $(BL)/emulator.o
	$(CC) -I $(BL) -o chip8_emulator $(BL)/sdlUi.o $(BL)/emulator.o -lSDL2
