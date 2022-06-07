CC = "gcc"
BL = "build"

main:
	$(CC) -I . -c sdlUi.c -o $(BL)/sdlUi.o -lSDL -g
	$(CC) -I . -c emulator.c -o $(BL)/emulator.o -g
	$(CC) -I $(BL) -o chip8_emulator $(BL)/sdlUi.o $(BL)/emulator.o -lSDL -g


clean:
	rm $(BL)/*.o
