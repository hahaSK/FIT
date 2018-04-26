cmake_minimum_required(VERSION 3.8)
project(codeblocks)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c proj3.h)
add_executable(codeblocks ${SOURCE_FILES})