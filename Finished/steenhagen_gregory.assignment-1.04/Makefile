rlg327: dungeon.o rlg327.o binheap.o character.o
	gcc dungeon.o binheap.o character.o rlg327.o -o rlg327 -lm
character.o: character.c character.h
	gcc -Wall -Werror -g character.c -c
dungeonGen.o: dungeon.c dungeon.h
	gcc -Wall -Werror -g dungeon.c -c
binheap.o: binheap.c binheap.h
	gcc -Wall -Werror -g binheap.c -c
rlg327.o: rlg327.c dungeon.h binheap.h character.h
	gcc -Wall -Werror -g rlg327.c -c
clean:
	rm -f dungeon.o
	rm -f rlg327
	rm -f rlg327.o
	rm -f character.o
	rm -f binheap.o
	rm -f *~
