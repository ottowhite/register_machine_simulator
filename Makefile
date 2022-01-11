CC 			= gcc
CFLAGS 	= -lm
BUILD 	= main

all: $(BUILD)
main: main.c 

clean:
	rm -rf build
