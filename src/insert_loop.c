//
// Created by yzy on 3/13/16.
//

#include "insert_loop.h"
#include "main_loop.h"
#include "file_sl.h"
#include "draw_ui.h"
#include "normal_loop.h"

int insert_mode_process(int key_down)
{
    switch (key_down)
    {
        case '\x1b':  //Esc
            mode_flag = NORMAL_MODE;
            break;

        case '\t':
            add_char(cur_file, cur_line + cur_top - 1, cur_column + cur_left - 1, ' ');
            add_char(cur_file, cur_line + cur_top - 1, cur_column + cur_left - 1, ' ');
            add_char(cur_file, cur_line + cur_top - 1, cur_column + cur_left - 1, ' ');
            add_char(cur_file, cur_line + cur_top - 1, cur_column + cur_left - 1, ' ');
            cursor_right();
            cursor_right();
            cursor_right();
            cursor_right();
            break;

        default:
            add_char(cur_file, cur_line + cur_top - 1, cur_column + cur_left - 1, (char) key_down);
            cursor_right();
            break;
    }
    return 0;
}
