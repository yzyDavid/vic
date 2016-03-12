//
// Created by yzy on 3/12/16.
//
#include <stdio.h>
#include <stdlib.h>

#include "main_loop.h"
#include "file_struct.h"
#include "draw_ui.h"

static int normal_mode_process(int keydown);

int mode_flag = NORMAL_MODE;

int main_loop()
{
    //This function assume the display back is disabled.
    int keydown;
    while ((keydown = getchar()))
    {
        switch (mode_flag)
        {
            case NORMAL_MODE:
                normal_mode_process(keydown);
                break;

            default:
                break;
        }
        redraw_ui();
    }
    return 0;
}

static int normal_mode_process(int keydown)
{
    switch (keydown)
    {
        case 'q':
            exit(0);
            break;

        case 'h':
            break;

        case 'l':
            break;

        case 'j':
            break;

        case 'k':
            break;

        default:
            break;
    }
    return 0;
}
