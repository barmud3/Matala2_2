CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -L. -lcodecA -lcodecB
LIBS = -lm

all: copy cmp encode decode stshell

copy: copy.c libcodecA.so libcodecB.so
	$(CC) $(CFLAGS) -o copy copy.c $(LDFLAGS) $(LIBS)

cmp: cmp.c libcodecA.so libcodecB.so
	$(CC) $(CFLAGS) -o cmp cmp.c $(LDFLAGS) $(LIBS)

encode: encode.c libcodecA.so
	$(CC) $(CFLAGS) -o encode encode.c $(LDFLAGS) $(LIBS)

decode: decode.c libcodecB.so
	$(CC) $(CFLAGS) -o decode decode.c $(LDFLAGS) $(LIBS)

stshell: stshell.c stshell.h
	$(CC) $(CFLAGS) -o stshell stshell.c $(LDFLAGS) $(LIBS)

libcodecA.so: codecA.c 
	$(CC) $(CFLAGS) -fPIC -c codecA.c
	$(CC) $(CFLAGS) -shared -o libcodecA.so codecA.o

libcodecB.so: codecB.c 
	$(CC) $(CFLAGS) -fPIC -c codecB.c
	$(CC) $(CFLAGS) -shared -o libcodecB.so codecB.o

clean:
	rm -f copy cmp encode decode stshell libcodecA.so libcodecB.so *.o

.DEFAULT_GOAL := all