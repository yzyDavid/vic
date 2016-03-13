//
// Created by yzy on 3/13/16.
//

#include "insert_loop.h"
#include "main_loop.h"

int insert_mode_process(int key_down)
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
