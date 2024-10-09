cmake_minimum_required(VERSION 3.27)
project(simple_tray_program C)

add_compile_options(-Wall -Wextra -ansi -pedantic-errors -std=c11)

add_executable(simple_tray_program WIN32 main.c)
