CC 			= gcc
CFLAGS 	= -lm
BUILD 	= main

all: $(BUILD)

main: main.c main.h

clean:
	rm -rf $(BUILD)
