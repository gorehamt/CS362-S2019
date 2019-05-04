CFLAGS= -Wall -fpic -lm -std=c99

all: 
    gcc -o testme testme.c -g $(CFLAGS)
    ./testme

clean:
    rm -f *.o