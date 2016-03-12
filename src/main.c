//
// Created by yzy on 3/12/16.
// This file contains the entry of the program.
//
#include <string.h>

#include "draw_ui.h"
#include "termios_set.h"
#include "main_loop.h"
#include "file_struct.h"

int main(int argc, char *argv[])
{
    switch (argc)
    {
        default:
        case 1:
            cur_file_name[0] = 0;
            break;
        case 2:
            strcpy(cur_file_name, argv[1]);
            break;
    }
    redraw_ui();
    init_display_back();
    disable_display_back();
    main_loop();
    enable_display_back();

    return 0;
}