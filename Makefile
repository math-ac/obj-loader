CC = clang
CFLAGS = -Wall -lglut -lGL -lGLU -lGLEW
BIN = loader

loader: loader.c
	$(CC) loader.c objl.c -o loader $(CFLAGS)
	
test: test.c
	$(CC) test.c objl.c -o test $(CFLAGS)
	
clean:
	rm loader test


