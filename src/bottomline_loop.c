//
// Created by yzy on 3/18/16.
//
#include <string.h>

#include "bottomline_loop.h"
#include "draw_ui.h"
#include "file_struct.h"
#include "main_loop.h"
#include "highlight.h"
#include "file_sl.h"

int bottomline_sub_mode = BOTTOM_LINE_EXCEPT;

int bottomline_mode_process(int key_down)
{
    int text_length = 0;
    int exist_flag = 0;
    text_length = strlen(bottomline_text);
    switch (key_down)
    {
        case '\n':
        case '\x0d':
        case '\x00':
            switch (bottomline_sub_mode)
            {
                case BOTTOM_LINE_FILENAME_SAVE:
                    strcpy(cur_file_name, bottomline_text);
                    mode_flag = NORMAL_MODE;
                    break;

                case BOTTOM_LINE_FILENAME_OPEN:
                    strcpy(cur_file_name, bottomline_text);
                    mode_flag = NORMAL_MODE;
                    v_load_file(cur_file_name, cur_file);
                    determine_file_type(cur_file_name);
                    break;

                default:
                    mode_flag = NORMAL_MODE;
                    break;
            }
            break;

        case '\x1b':    //Esc.
            mode_flag = NORMAL_MODE;
            break;

        case '\x7f':  //backspace
        case '\x08':    //backspace in windows.
            bottomline_text[text_length - 1] = 0;
            break;

        default:
            for (char *i = word_char_list; *i != 0; i++)
            {
                if (key_down == *i)
                {
                    exist_flag = 1;
                }
            }
            if (key_down == '.' || key_down == '-')
            {
                exist_flag = 1;
            }

            if (!exist_flag)
            {
                return -1;
            }

            if (text_length < CONSOLE_COLUMNS - 2)
            {
                bottomline_text[text_length] = (char) key_down;
            }
            else
            {
                return -1;
            }
            break;
    }
    return 0;
}

