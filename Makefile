CC = clang
CFLAGS = -Wall -lglut -lGL -lGLU -lGLEW
BIN = loader

loader: loader.c
	$(CC) loader.c objl.c -o loader $(CFLAGS)

robot: robot.c
	$(CC) robot.c -o robot $(CFLAGS)

test: test.c
	$(CC) test.c objl.c -o test $(CFLAGS)

clean:
	rm loader test


