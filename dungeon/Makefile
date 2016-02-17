rlg327: dungeonGen.o rlg327.o binheap.o character.o
	gcc dungeonGen.o binheap.o character.o rlg327.o -o rlg327 -lm
character.o: character.c character.h
	gcc -Wall -Werror -g character.c -c
dungeonGen.o: dungeonGen.c dungeonGen.h
	gcc -Wall -Werror -g dungeonGen.c -c
binheap.o: binheap.c binheap.h
	gcc -Wall -Werror -g binheap.c -c
rlg327.o: rlg327.c dungeonGen.h binheap.h character.h
	gcc -Wall -Werror -g rlg327.c -c
clean:
	rm -f dungeonGen.o
	rm -f rlg327
	rm -f rlg327.o
	rm -f character.o
	rm -f binheap.o
	rm -f *~
