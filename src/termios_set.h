//
// Created by yzy on 3/12/16.
//

//To disable the display back
//Warning!! This part is POSIX only!!!
//to use it under windows, we ought to find another method.

#ifndef VIC_TERMIOS_SET_H
#define VIC_TERMIOS_SET_H

#include <stdio.h>

#ifdef __VIC_WIN

#include <windows.h>

#endif

#include "draw_ui.h"

#ifdef __VIC_WIN

extern HANDLE hStdIn;
extern HANDLE hStdOut;

#endif

int init_display_back();

int disable_display_back();

int enable_display_back();

int hide_cursor();

int show_cursor();

#ifdef __VIC_WIN

int __get_self_window_win();

int __get_char_win();

#endif

#endif //VIC_TERMIOS_SET_H
