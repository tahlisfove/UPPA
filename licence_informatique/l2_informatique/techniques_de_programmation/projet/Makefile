CC = gcc
CFLAGS = -std=c89 -pedantic -Wall -Werror -g `pkg-config libxml-2.0 --cflags`
LDFLAGS = `pkg-config libxml-2.0 --libs-only-L`
LDLIBS = `pkg-config libxml-2.0 --libs-only-l`
RM = rm -fv

.PHONY: all clean
all: bm.out

base.o : base.c 
		$(CC) $(CFLAGS) -c -o $@ $^ 
facility.o : facility.c
		$(CC) $(CFLAGS) -c -o $@ $^ 
bm.out: bm.c base.o facility.o
		$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
clean:
		$(RM) *.o *.out