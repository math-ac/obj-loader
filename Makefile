CC = clang
CFLAGS = -g -Wall -lglut -lGL -lGLU -lGLEW -lm
BIN = loader

tour: tour.c
	$(CC) tour.c objl.c -o tour $(CFLAGS)

clean:
	rm tour


