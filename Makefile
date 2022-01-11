CC 			= gcc
CFLAGS 	= -lm
BUILD 	= main
SRC 		= main.c encode.c decode.c execute.c pretty_print.c
HEADERS = main.h encode.h decode.h execute.h pretty_print.h

all: $(BUILD)

main: $(SRC) $(HEADERS)

clean:
	rm -rf $(BUILD)
