//
// Created by yzy on 3/13/16.
//

#include "main.h"

#ifdef __VIC_WIN

#include <conio.h>

#endif

#include <stdio.h>
#include "insert_loop.h"
#include "main_loop.h"
#include "file_sl.h"
#include "draw_ui.h"
#include "normal_loop.h"
#include "log_module.h"
#include "termios_set.h"

int insert_mode_process(int key_down)
{
    unsigned int length = 0;
    length = get_length(get_line(cur_file, cur_line + cur_top - 1));

    unsigned int actual_column = 0;
//    unsigned int actual_line = 0;
    actual_column = cur_column + cur_left - 1;
//    actual_line = cur_line + cur_top - 1;

#ifdef __VIC_POSIX
    int second_key_down = 0;
#endif

    if (key_down < 0)
    {
        return -1;
    }

    switch (key_down)
    {
        //arrow keys is also start with x1b!
        case '\x1b':  //Esc
#ifdef __VIC_POSIX
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
#endif

#ifdef __VIC_WIN
            mode_flag = NORMAL_MODE;
            /*
            second_key_down = getch();
            switch (second_key_down)
            {
                case '\x1b':
                    mode_flag = NORMAL_MODE;
                    break;

                default:
                    break;
            }
             */

#endif
            break;

#ifdef __VIC_WIN

            /*
        case '\xe0':    //first ascii of arrow keys.
            switch (getch())
            {
                case '\x48':    //up
                    cursor_up();
                    break;

                case '\x50':    //down
                    cursor_down();
                    break;

                case '\x4b':    //left
                    cursor_left();
                    break;

                case '\x4d':    //right
                    cursor_right();
                    break;

                default:
                    break;
            }
            break;
             */

        case 0x000000e0:    //first(or last maybe?) ascii of arrow keys.
            switch (__get_char_win())
            {
                case '\x48':    //up
                    cursor_up();
                    break;

                case '\x50':    //down
                    cursor_down();
                    break;

                case '\x4b':    //left
                    cursor_left();
                    break;

                case '\x4d':    //right
                    cursor_right();
                    break;

                default:
                    break;
            }

#endif

        case '\x7f':  //backspace
        case '\x08':    //backspace in windows.
            if (actual_column != 1)
            {
                del_char(get_line(cur_file, cur_top + cur_line - 1), cur_left + cur_column - 3);
                cursor_left();
                changed_flag = CHANGED;
            }
            else
            {
                if (length == 0)
                {
                    delete_line(cur_file, cur_top + cur_line - 1);
                    cursor_up();
                    goto_line_end();
                }
                else
                {
                    connect_line(cur_file, cur_top + cur_line - 1);
                    cursor_up();
                }
            }
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

        case '\n':  //Enter:
        case '\x0d':    //might be \r ? used in Windows.
            split_line(cur_file, cur_top + cur_line - 1, cur_left + cur_column - 2);
            cursor_down();
            goto_line_start();
            changed_flag = CHANGED;
            break;

        default:
            add_char(cur_file, cur_line + cur_top - 1, cur_column + cur_left - 1, (char) key_down);
            cursor_right();
            changed_flag = CHANGED;
            print_log("default");
            break;
    }
    return 0;
}

