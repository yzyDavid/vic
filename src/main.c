//
// Created by yzy on 3/12/16.
// This file contains the entry of the program.
//
#include <string.h>
#include <stdlib.h>

#include "draw_ui.h"
#include "termios_set.h"
#include "main_loop.h"
#include "file_struct.h"
#include "file_sl.h"
#include "main.h"
#include "log_module.h"

int main(int argc, char *argv[])
{
    init_log();
    cur_file = malloc(sizeof(v_file_text));
    switch (argc)
    {
        default:
        case 1:
            cur_file_name[0] = 0;
            v_new_file(cur_file);
            break;
        case 2:
            strcpy(cur_file_name, argv[1]);
            v_load_file(cur_file_name, cur_file);
            break;
    }

    init_global();

    parse_highlighting(cur_file);
    redraw_ui();
    init_display_back();
    disable_display_back();
    main_loop();
    enable_display_back();

    return 0;
}

int init_global()
{
    cur_top = 1;
    cur_left = 1;
    cur_line = 1;
    cur_column = 1;

    return 0;
}