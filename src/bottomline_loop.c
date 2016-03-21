//
// Created by yzy on 3/18/16.
//
#include <string.h>

#include "bottomline_loop.h"
#include "draw_ui.h"

int bottomline_sub_mode = BOTTOM_LINE_EXCEPT;

int bottomline_mode_process(int key_down)
{
    int text_length = 0;
    text_length = strlen(bottomline_text);
    switch (key_down)
    {
        case '\n':
        case '\x0d':
            switch (bottomline_sub_mode)
            {
                case BOTTOM_LINE_FILENAME:
                    break;

                default:
                    break;
            }
            break;

        default:
            if(text_length<CONSOLE_COLUMNS -2)
            {
                bottomline_text[text_length] = (char) key_down;
            }
            else
            {

            }
            break;
    }
    return 0;
}

