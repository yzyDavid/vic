//
// Created by yzy on 3/12/16.
//
#include <stdio.h>
#include <stdlib.h>

#include "main_loop.h"
#include "file_struct.h"
#include "draw_ui.h"
#include "termios_set.h"

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
                exit(0);
            }
            else
            {

            }
            break;

            //belows hjkl for cursor moving.
        case 'h':
            break;

        case 'l':
            break;

        case 'j':
            break;

        case 'k':
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
    return -1;
}

int cursor_right()
{
    return -1;
}

int cursor_up()
{
    return -1;
}

int cursor_down()
{
    return -1;
}