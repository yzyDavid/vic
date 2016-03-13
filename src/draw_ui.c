//
// Created by yzy on 3/12/16.
//

#include <stdio.h>
#include <string.h>

#include "draw_ui.h"
#include "file_struct.h"

//This globals defines the position of "cursor".
//relative to the line3-23 (actually contains the file) part.
unsigned int cur_line;
unsigned int cur_column;

//This globals defines the position of the screen.
//relative to the file.
unsigned int cur_top;
unsigned int cur_left;

int redraw_ui()
{
    char title_bar[CONSOLE_COLUMNS + 1] =
            "vic - ";
    char menu_bar[CONSOLE_COLUMNS + 1] =
            "New File[1] Save[2]                                                   -- menu --";
    char status_bar[CONSOLE_COLUMNS + 1] =
            "status:                                                                         ";
    if (cur_file_name[0] == 0)
        strcat(title_bar, "New File");
    else
        strcat(title_bar, cur_file_name);

    printf("\n");
    printf(CLEAR);

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
    //actually a screen contains 21 lines.
    for (int i = 0; i < 21; i++)
    {
        int finished_flag = 0;
        v_line *current_line = get_line(cur_file, i + cur_top);
        if (current_line != NULL)
        {
            for (int j = 0; j < 80; j++)
            {
                if (finished_flag || current_line->text[cur_left + j - 1] == 0)
                {
                    finished_flag = 1;
                    printf(" ");
                }
                else
                {
                    printf("%c", current_line->text[cur_left + j - 1]);
                }
            }
        }
        printf("\n");
    }

    //Line 24
    printf(L_BLUE);
    printf(status_bar);
    printf(NONE);

    return 0;
}