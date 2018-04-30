cmake_minimum_required(VERSION 3.10)
project(The_Senate_Bus_Problem)

set(CMAKE_C_STANDARD 99)

# create exacutables in src/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_C_FLAGS -lpthread)

add_executable(proj2 proj2.c BusSolution.c BusSolution.h proj2.h)