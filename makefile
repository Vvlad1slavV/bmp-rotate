main: main.c
		mkdir -p build
		gcc main.c bmp.c util.c error.c bmp_io.c bmp_rotate.c -o build/bmp_rotate -std=c18 -pedantic -Wall -Werror