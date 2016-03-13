//
// Created by yzy on 3/12/16.
//

//To disable the display back
//Warning!! This part is POSIX only!!!
//to use it under windows, we ought to find another method.

#ifndef VIC_TERMIOS_SET_H
#define VIC_TERMIOS_SET_H

#include "draw_ui.h"

int init_display_back();
int disable_display_back();
int enable_display_back();

inline int hide_cursor()
{
    printf(HIDE_CURSOR);
    return 0;
}

inline int show_cursor()
{
    printf(SHOW_CURSOR);
    return 0;
}

#endif //VIC_TERMIOS_SET_H
