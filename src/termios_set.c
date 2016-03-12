//
// Created by yzy on 3/12/16.
//

#include <termios.h>

#include "termios_set.h"

static struct termios disabled;
static struct termios enabled;

int init_dispaly_back()
{
    tcgetattr(0, &enabled);
    disabled = enabled;
    disabled.c_lflag &= ~ICANON;
    disabled.c_lflag &= ~ECHO;
    disabled.c_cc[VMIN] = 1;
    disabled.c_cc[VTIME] = 0;
}

int diasble_display_back()
{
    tcsetattr(0, TCSANOW, &disabled);
}

int enable_display_back()
{
    tcsetattr(0, TCSANOW, &enabled);
}