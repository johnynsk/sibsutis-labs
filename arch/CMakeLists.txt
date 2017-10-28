cmake_minimum_required(VERSION 3.10)
project(arch)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c)
set(LIB_FILES  lib/memory.h lib/registers.h lib/command.h lib/term.h lib/big_chars.h)
set(REAL_FILES lib/memory.c lib/registers.c lib/command.c lib/term.c lib/big_chars.c)

add_executable(arch ${SOURCE_FILES} ${LIB_FILES} ${REAL_FILES})
