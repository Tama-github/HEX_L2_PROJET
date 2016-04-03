HEX: HEX.o Interface.o hexagone.o
		gcc HEX.o Interface.o hexagone.o -o HEX -g -ggdb `sdl-config --cflags --libs` -lSDL_image

HEX.o: src/HEX.c
		gcc -c src/HEX.c -Wall -g -ggdb -O0

Interface.o: src/Interface.c
		gcc -c src/Interface.c -Wall -g -ggdb -O0

hexagone.o: src/hexagone.c
		gcc -c src/hexagone.c -Wall -g -ggdb -O0

clean:
		rm -f *.o HEX
