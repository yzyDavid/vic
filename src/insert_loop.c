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
    unsigned int length = 0;
    length = get_length(get_line(cur_file, cur_line + cur_top - 1));

    switch (key_down)
    {
        case '\x1b':  //Esc
            mode_flag = NORMAL_MODE;
            break;

        case '\x7f':  //backspace
            del_char(get_line(cur_file, cur_top + cur_line - 1), cur_left + cur_column - 3);
            cursor_left();
            changed_flag = CHANGED;
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
            changed_flag = CHANGED;
            break;

        case '\n':  //Enter: not tested.
            changed_flag = CHANGED;
            break;

        default:
            if(length!=0)
            {
                add_char(cur_file, cur_line + cur_top - 1, cur_column + cur_left - 1, (char) key_down);
            }
            else
            {
                add_char(cur_file, cur_line + cur_top - 1, cur_column + cur_left - 1, (char) key_down);
            }
            cursor_right();
            changed_flag = CHANGED;
            break;
    }
    return 0;
}
