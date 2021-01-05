cmake_minimum_required(VERSION 3.10.2)
project(bmp-rotate C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c18 -pedantic -Wall -Werror")

add_executable(bmp-rotate src/main.c src/bmp.h src/bmp_rotate.h src/bmp_io.h src/util.h src/bmp.c src/error.h src/error.c src/bmp_io.c src/util.c src/bmp_rotate.c src/bmp_struct.h)