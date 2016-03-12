//
// Created by yzy on 3/12/16.
// This file contains the entry of the program.
//
#include "draw_ui.h"
#include "termios_set.h"

int main(int argc, char* argv[])
{
    init_display_back();
    disable_display_back();
    redraw_ui();
    enable_display_back();

    return 0;
}