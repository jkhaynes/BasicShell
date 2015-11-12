CC = g++
CFLAGS = -g -O2
OBJECTS = main.o foreground.o background.o piped.o
#include directory
INCLUDES = -I./inc
STUDENTID = jkhaynes

all: wsh

wsh : $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o wsh

main.o : src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/main.c

foreground.o : src/foreground.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/foreground.c
	
background.o : src/background.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/background.c	

piped.o : src/piped.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/piped.c	

clean:	
	rm -f *.o wsh

	
	