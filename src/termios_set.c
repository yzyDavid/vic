//
// Created by yzy on 3/12/16.
//

#include <termios.h>
#include <stdio.h>

#include "termios_set.h"
#include "draw_ui.h"

static struct termios disabled;
static struct termios enabled;

int init_display_back()
{
    tcgetattr(0, &enabled);
    disabled = enabled;
    disabled.c_lflag &= ~ICANON;
    disabled.c_lflag &= ~ECHO;
    disabled.c_cc[VMIN] = 1;
    disabled.c_cc[VTIME] = 0;
    return 0;
}

int disable_display_back()
{
    tcsetattr(0, TCSANOW, &disabled);
    printf(HIDE_CURSOR);
    return 0;
}

int enable_display_back()
{
    tcsetattr(0, TCSANOW, &enabled);
    printf(NONE);
    printf(SHOW_CURSOR);
    return 0;
}

