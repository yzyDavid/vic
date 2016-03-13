//
// Created by yzy on 3/12/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "main_loop.h"
#include "file_struct.h"
#include "draw_ui.h"
#include "termios_set.h"
#include "file_sl.h"

static int normal_mode_process(int key_down);

static int insert_mode_process(int key_down);

int mode_flag = NORMAL_MODE;

int main_loop()
{
    //This function assume the display back is disabled.
    int key_down;
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
        redraw_ui();
    }
    return 0;
}

static int normal_mode_process(int key_down)
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
            mode_flag = INSERT_MODE;
            break;

        case 'd':   //delete.
            break;

        case 'o':   //open new line.
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

static int insert_mode_process(int key_down)
{
    switch (key_down)
    {
        case '\x1b':  //Esc
            mode_flag = NORMAL_MODE;
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
    if (cur_column == 1 && cur_left == 1)
    {
        return 0;
    }
    cur_column--;
    if (!is_position_in_file())
    {
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
    if (cur_column >= 80)
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
        if (length < cur_column)
        {
            cur_column = length;
        }
        return 1;
    }
    else if (cur_top > 1)
    {
        roll_downward(-1);
        return 1;
    }
    return -1;
}

int cursor_down()
{
    unsigned int lines = get_total_lines(cur_file);
    cur_line++;
    if (!is_position_in_file())
    {
        if(lines >= cur_line)
        {

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
        roll_downward(1);
        return 1;
    }
    else if (cur_line < SCREEN_LINES)
    {
        return 1;
    }
    return -1;
}

//This function judge if the position of cursor is contained in the file.
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
    if (cur_file_column > get_length(get_line(cur_file, cur_file_line)))
    {
        return 0;
    }

    return 1;
}
