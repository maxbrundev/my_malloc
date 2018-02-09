cmake_minimum_required(VERSION 3.9)
project(malloc C)

set(CMAKE_C_STANDARD 11)

include_directories("includes")

add_executable(malloc main.c src/malloc_perso.c includes/malloc_perso.h includes/my_put_char.h includes/my_put_number.h src/my_put_char.c src/my_put_number.c src/free_perso.c includes/free_perso.h)