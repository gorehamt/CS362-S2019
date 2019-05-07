CFLAGS= -Wall -fpic -coverage -lm -std=c99

buildAndRun:
	gcc -o testme testme.c $(CFLAGS)
	./testme
	gcov -b testme.c

clean:
	rm -f *.o testme.c.gcov testme.gcda testme.gcno testme


