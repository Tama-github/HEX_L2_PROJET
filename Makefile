HEX: HEX.o Interface.o hexagone.o board.o game.o
		gcc HEX.o Interface.o hexagone.o board.o game.o -o HEX -g -ggdb `sdl-config --cflags --libs` -lSDL_image

HEX.o: src/HEX.c
		gcc -c src/HEX.c -Wall -g -ggdb -O0

Interface.o: src/Interface.c
		gcc -c src/Interface.c -Wall -g -ggdb -O0

hexagone.o: src/hexagone.c
		gcc -c src/hexagone.c -Wall -g -ggdb -O0

board.o: src/board.c
		gcc -c src/board.c -Wall -g -ggdb -O0

game.o: src/game.c
		gcc -c src/game.c -Wall -g -ggdb -O0

clean:
		rm -f *.o HEX
