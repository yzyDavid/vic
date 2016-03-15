//
// Created by yzy on 3/12/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "main_loop.h"
#include "file_struct.h"
#include "draw_ui.h"
#include "normal_loop.h"
#include "insert_loop.h"

int mode_flag = NORMAL_MODE;

int main_loop()
{
    //This function assume the display back is disabled.
    int key_down = 0;
    while ((key_down = getchar()))
    {
        switch (mode_flag)
        {
            case NORMAL_MODE:
                normal_mode_process(key_down);
                break;

            case INSERT_MODE:
                insert_mode_process(key_down);
                break;

            case BOTTOMLINE_MODE:
                break;

            default:
                break;
        }
        parse_highlighting(cur_file);
        redraw_ui();
    }
    return 0;
}

//This function judge if the position of cursor is contained in the file.
//***!!! position available: including one pos at each end of line  !!!***
//return code:
//1 for True
//0 for False
int is_position_in_file()
{
    unsigned int cur_file_line;
    unsigned int cur_file_column;
    cur_file_line = cur_top + cur_line - 1;
    cur_file_column = cur_left + cur_column - 1;

    if (cur_file_line > get_total_lines(cur_file))
    {
        return 0;
    }
    if (cur_file_column > 1 + get_length(get_line(cur_file, cur_file_line)))
    {
        return 0;
    }

    return 1;
}


