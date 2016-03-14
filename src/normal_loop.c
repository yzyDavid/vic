//
// Created by yzy on 3/13/16.
//

#include <assert.h>
#include <stdlib.h>

#include "normal_loop.h"
#include "file_struct.h"
#include "draw_ui.h"
#include "main_loop.h"
#include "termios_set.h"
#include "file_sl.h"

int normal_mode_process(int key_down)
{
    switch (key_down)
    {
        case 'q':   //quit, is saved should be checked.
            if (changed_flag == UNCHANGED)
            {
                enable_display_back();
                set_cursor_pos(80, 24);
                exit(0);
            }
            else
            {

            }
            break;

            //belows hjkl for cursor moving.
            //aiming to disable moving cursor outside the file part.
        case 'h':
            cursor_left();
            break;

        case 'l':
            cursor_right();
            break;

        case 'j':
            cursor_down();
            break;

        case 'k':
            cursor_up();
            break;

        case 'w':   //word forward.
            break;

        case 'i':   //insert.
            mode_flag = INSERT_MODE;
            break;

        case 'a':   //append.
            cursor_right();
            mode_flag = INSERT_MODE;
            break;

        case 'd':   //delete a word.
            break;

        case 'x':   //delete a single char.
            break;

        case 'o':   //open new line.
            break;

        case '$':
            goto_line_end();
            break;

        case '^':   //goto fisrt char of line.
            break;

        case '0':   //goto fixed first column.
            break;

        case ':':   //bottom line command mode.
            break;

        case '/':    //bottom line and search.
            break;

        case '2':
        case 's':
            v_save_file(cur_file_name, cur_file);
            break;

        default:
            break;
    }
    return 0;
}


//functions below is the implements of moving the cursor.
//only should be called when its under normal or insert mode.
//return code:
//0: move failed.
//1: move success.
//-1: exceptions.
int cursor_left()
{
    unsigned int lines;
    lines = get_total_lines(cur_file);
    if (cur_column == 1 && cur_left == 1)
    {
        return 0;
    }
    cur_column--;
    if (!is_position_in_file())
    {
        if (cur_line + cur_top - 1 <= lines)
        {
            return 1;
        }
        cur_column++;
        return 0;
    }
    else if (cur_column > 1)
    {
        return 1;
    }
    else if (cur_left > 1)
    {
        cur_column++;
        roll_rightward(-1);
        return 1;
    }
    return -1;
}

int cursor_right()
{
    assert(cur_column <= 80);
    ++cur_column;
    if (!is_position_in_file())
    {
        cur_column--;
        return 0;
    }
    else if (cur_column >= 80)
    {
        --cur_column;
        roll_rightward(1);
        return 1;
    }
    else
    {
        return 1;
    }
    return -1;
}

int cursor_up()
{
    unsigned int length = 0;
    if (cur_line == 1 && cur_top == 1)
    {
        return 0;
    }
    else if (cur_line > 1)
    {
        cur_line--;
        length = (int) strlen((const char *) get_line(cur_file, cur_line + cur_top - 1));
        length = (length == 0) ? 1 : length;
        if (length < cur_column)
        {
            cur_column = length;
        }
        return 1;
    }
    else if (cur_top > 1)
    {
        roll_downward(1);
        return 1;
    }
    return -1;
}

//Have bugs in calc position.
// test data:
// cur_left     21
// cur_column   80
// length       0
int cursor_down()
{
    unsigned int lines = get_total_lines(cur_file);
    unsigned int length;
    cur_line++;
    length = (unsigned int) strlen((const char *) get_line(cur_file, cur_line + cur_top - 1));
    length = (length == 0) ? 1 : length;
    if (!is_position_in_file())
    {
        //When the cursor is at the end of a line
        //length == cur_left + cur_column -1
        //always works.
        if (lines >= cur_line + cur_top - 1)
        {
            /*
            if (length > cur_left + SCREEN_COLUMNS)
            {
                cur_column = SCREEN_COLUMNS;
                cur_left = length - cur_column + 1;
                return 1;
            }
            else
            {
                cur_column = length - cur_left + 1;
                return 1;
            }
             */
            int tmp = 0;
            tmp = length - cur_left + 1;
            if (tmp < 1)
            {
                cur_left -= 1 - tmp;
                tmp = 1;
            }
            cur_column = (unsigned int) tmp;
            return 1;
        }
        else
        {
            --cur_line;
            return 0;
        }
    }
    else if (cur_line >= SCREEN_LINES)
    {
        --cur_line;
        roll_downward(-1);
        return 1;
    }
    else if (cur_line < SCREEN_LINES)
    {
        return 1;
    }
    return -1;
}

int goto_line_end()
{
    unsigned int actual_column = 0;
    unsigned int length = 0;
    length = (unsigned int) strlen((const char *) get_line(cur_file, cur_line + cur_top - 1));
    length = (length == 0) ? 1 : length;
    actual_column = cur_left + cur_column - 1;
    if (length > actual_column)
    {
        for (int i = 0; i < length - actual_column; i++)
        {
            cursor_right();
        }
    }
    else
    {
        for (int i = 0; i < actual_column - length; i++)
        {
            cursor_left();
        }
    }
    return 0;
}
