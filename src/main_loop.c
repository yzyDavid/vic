//
// Created by yzy on 3/12/16.
//
#include <stdio.h>

#include "main_loop.h"
#include "file_struct.h"
#include "draw_ui.h"

int main_loop()
{
    //This function assume the display back is disabled.
    char keydown;
    while (keydown = getchar())
    {
        switch(keydown)
        {
            default:
                break;
        }
        redraw_ui();
    }
}

