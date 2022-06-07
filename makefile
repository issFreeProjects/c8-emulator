CC = "gcc"
BL = "build"
PATH_FLAG = "-I"
DEBUG_FLAG = "-g"

main:
	$(CC) $(PATH_FLAG) . -c sdlUi.c -o $(BL)/sdlUi.o -lSDL
	$(CC) $(PATH_FLAG) . -c c8_emulator.c -o $(BL)/c8_emulator.o
	$(CC) $(PATH_FLAG) . -c main.c -o $(BL)/main.o
	$(CC) $(PATH_FLAG) $(BL) -o emulator $(BL)/main.o $(BL)/sdlUi.o $(BL)/c8_emulator.o -lSDL


debug:
	$(CC) $(PATH_FLAG) . -c sdlUi.c -o $(BL)/sdlUi.o -lSDL $(DEBUG_FLAG)
	$(CC) $(PATH_FLAG) . -c c8_emulator.c -o $(BL)/c8_emulator.o $(DEBUG_FLAG)
	$(CC) $(PATH_FLAG) . -c main.c -o $(BL)/main.o $(DEBUG_FLAG)
	$(CC) $(PATH_FLAG) $(BL) -o emulator $(BL)/main.o $(BL)/sdlUi.o $(BL)/c8_emulator.o -lSDL $(DEBUG_FLAG)


clean:
	rm $(BL)/*.o
