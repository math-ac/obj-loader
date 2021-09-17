CC = clang
CFLAGS = -Wall -lglut -lGL -lGLU -lGLEW
BIN = loader

loader: loader.c
	$(CC) loader.c objl.c -o loader $(CFLAGS)
	
clean:
	rm loader


