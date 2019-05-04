CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme.o: 
    gcc -c testme.c -g $(CFLAGS)
    ./testme

clean:
    rm -f *.o