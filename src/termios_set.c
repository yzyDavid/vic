//
// Created by yzy on 3/12/16.
//
#include "main.h"

#ifdef __VIC_POSIX
#include <termios.h>
#endif
#include <stdio.h>

#include "termios_set.h"
#include "draw_ui.h"

#ifdef __VIC_POSIX
static struct termios disabled;
static struct termios enabled;
#endif

int init_display_back()
{
#ifdef __VIC_POSIX
    tcgetattr(0, &enabled);
    disabled = enabled;
    disabled.c_lflag &= ~ICANON;
    disabled.c_lflag &= ~ECHO;
    disabled.c_cc[VMIN] = 1;
    disabled.c_cc[VTIME] = 0;
#endif
    return 0;
}

int disable_display_back()
{
#ifdef __VIC_POSIX
    tcsetattr(0, TCSANOW, &disabled);
#endif
    return 0;
}

int enable_display_back()
{
#ifdef __VIC_POSIX
    tcsetattr(0, TCSANOW, &enabled);
    printf(NONE);
#endif
    return 0;
}

int hide_cursor()
{
#ifdef __VIC_POSIX
    printf(HIDE_CURSOR);
#endif
    return 0;
}

int show_cursor()
{
#ifdef __VIC_POSIX
    printf(SHOW_CURSOR);
#endif
    return 0;
}

