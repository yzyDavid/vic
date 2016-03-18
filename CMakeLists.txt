cmake_minimum_required(VERSION 3.3)
project(vic)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_C_COMPILER clang)
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_C_COMPILER gcc)
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

set(SOURCE_FILES_TEST src/test/testmain.c src/test/printf_color.c)
set(SOURCE_FILES src/main.c
        src/file_struct.c
        src/file_struct.h
        src/draw_ui.c
        src/draw_ui.h
        src/file_sl.c
        src/file_sl.h
        src/termios_set.c
        src/termios_set.h
        src/main_loop.c
        src/main_loop.h
        src/main.h
        src/normal_loop.c
        src/normal_loop.h
        src/insert_loop.c
        src/insert_loop.h
        src/highlight.c
        src/highlight.h
        src/log_module.c
        src/log_module.h src/bottomline_loop.c src/bottomline_loop.h)
add_executable(vic_test ${SOURCE_FILES_TEST})
add_executable(vic ${SOURCE_FILES})