//
// Created by yzy on 3/13/16.
//

#include <stdio.h>
#include "insert_loop.h"
#include "main_loop.h"
#include "file_sl.h"
#include "draw_ui.h"
#include "normal_loop.h"

int insert_mode_process(int key_down)
{
    unsigned int length = 0;
    length = get_length(get_line(cur_file, cur_line + cur_top - 1));

    int second_key_down = 0;

    switch (key_down)
    {
        //arrow keys is also start with x1b!
        case '\x1b':  //Esc
            second_key_down = getchar();
            switch (second_key_down)    //double stroke Esc to return to normal mode.
            {
                case '\x1b':
                    mode_flag = NORMAL_MODE;
                    break;

                case '\x5b':
                    second_key_down = getchar();
                    switch (second_key_down)
                    {
                        case '\x41':     //up
                            cursor_up();
                            break;

                        case '\x42':     //down
                            cursor_down();
                            break;

                        case '\x43':     //right
                            cursor_right();
                            break;

                        case '\x44':     //left
                            cursor_left();
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
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
            if (length != 0)
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
