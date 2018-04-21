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
set(LIB_FILES  lib/log.h lib/memory.h lib/registers.h lib/command.h lib/units.h lib/term.h lib/big_chars.h lib/char.h lib/keys.h lib/ui.h)
set(REAL_FILES lib/log.c lib/memory.c lib/registers.c lib/command.c lib/units.c lib/term.c lib/big_chars.c lib/char.c lib/keys.c lib/ui.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")
#set(TERM_LIB_FILES lib/term.h lib/term.c lib/big_chars.h lib/big_chars.c char.h char.c lib/keys.h lib/keys.c lib/ui.h lib/ui.c)
add_compile_options(-std=c11)
add_compile_options(-std=gnu11)

add_executable(arch utils/arch.c ${LIB_FILES} ${REAL_FILES})
add_executable(genc utils/genc.c ${LIB_FILES} ${REAL_FILES} ${TERM_LIB_FILES})
add_executable(sac utils/sac.c ${LIB_FILES} ${REAL_FILES})
#add_executable(sbc utils/sbc.c ${LIB_FILES} ${REAL_FILES})

