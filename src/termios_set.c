//
// Created by yzy on 3/12/16.
//

#ifdef __linux
#include <termios.h>
#endif
#include <stdio.h>

#include "termios_set.h"
#include "draw_ui.h"

#ifdef __linux
static struct termios disabled;
static struct termios enabled;
#endif

int init_display_back()
{
#ifdef __linux
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
#ifdef __linux
    tcsetattr(0, TCSANOW, &disabled);
#endif
    return 0;
}

int enable_display_back()
{
#ifdef __linux
    tcsetattr(0, TCSANOW, &enabled);
    printf(NONE);
#endif
    return 0;
}

int hide_cursor()
{
#ifdef __linux
    printf(HIDE_CURSOR);
#endif
    return 0;
}

int show_cursor()
{
#ifdef __linux
    printf(SHOW_CURSOR);
#endif
    return 0;
}

