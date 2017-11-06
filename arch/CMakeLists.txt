cmake_minimum_required(VERSION 3.0)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "-std=gnu11 -std=c11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

project(arch)

use_cxx11()

set(CMAKE_CXX_FLAGS "-std=c11 -std=gnu11 ${CMAKE_CXX_FLAGS}")
set(SOURCE_FILES main.c)
set(LIB_FILES  lib/memory.h lib/registers.h lib/command.h lib/units.h lib/term.h lib/big_chars.h char.h lib/keys.h lib/ui.h)
set(REAL_FILES lib/memory.c lib/registers.c lib/command.c lib/units.c lib/term.c lib/big_chars.c char.c lib/keys.c lib/ui.c)
#set(TERM_LIB_FILES lib/term.h lib/term.c lib/big_chars.h lib/big_chars.c char.h char.c lib/keys.h lib/keys.c lib/ui.h lib/ui.c)
add_compile_options(-std=c11)
add_compile_options(-std=gnu11)


add_executable(arch ${SOURCE_FILES} ${LIB_FILES} ${REAL_FILES})
add_executable(lab1 lab/lab1.c ${LIB_FILES} ${REAL_FILES})
#add_executable(lab2 lab/lab2.c ${TERM_LIB_FILES})
add_executable(lab3 lab/lab3.c ${LIB_FILES} ${REAL_FILES} ${TERM_LIB_FILES})
add_executable(genc lab/genc.c ${LIB_FILES} ${REAL_FILES} ${TERM_LIB_FILES})
#add_executable(lab4 lab/lab4.c ${LIB_FILES} ${REAL_FILES} ${TERM_LIB_FILES})
#add_executable(lab5 lab/lab5.c ${LIB_FILES} ${REAL_FILES} ${TERM_LIB_FILES})
