//
// Created by yzy on 3/12/16.
//

#include <stdio.h>
#include "draw_ui.h"

unsigned int cur_line;
unsigned int cur_page;
unsigned int cur_column;

int redraw_ui()
{
    char title_bar[CONSOLE_COLUMNS] = "vic";
    char menu_bar[CONSOLE_COLUMNS] = "menu";
    char status_bar[CONSOLE_COLUMNS] = "status";
    //Line 1
    printf(L_CYAN);
    printf(title_bar);
    printf(NONE);
    printf("\n");
    //Line 2
    printf(L_GREEN);
    printf(menu_bar);
    printf(NONE);
    printf("\n");


    //Line 3 to 23
    for(int i=2;i<23;i++)
    {
        printf("\n");
    }

    //Line 24
    printf(L_BLUE);
    printf(status_bar);
    printf(NONE);
    printf("\n");

    return 0;
}