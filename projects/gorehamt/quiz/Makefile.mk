CFLAGS= -Wall -fpic -lm -std=c99

all: 
    gcc -c testme testme.c -g $(CFLAGS)
    ./testme

clean:
    rm -f *.o