//
// Created by yzy on 3/12/16.
//

#include <stdio.h>
#include <string.h>

#include "draw_ui.h"
#include "file_struct.h"
#include "main_loop.h"

//This globals defines the position of "cursor".
//relative to the line3-23 (actually contains the file) part.
unsigned int cur_line;
unsigned int cur_column;

//This globals defines the position of the screen.
//relative to the file.
unsigned int cur_top;
unsigned int cur_left;

char title_bar[CONSOLE_COLUMNS + 1];
char menu_bar[CONSOLE_COLUMNS + 1];
char status_bar[CONSOLE_COLUMNS + 1];
char status_bar_template[CONSOLE_COLUMNS + 1];

int redraw_ui()
{
    strcpy(title_bar,
           "vic - ");
    strcpy(menu_bar,
           "New File[1] Save[2,s]                                                 -- menu --");
    strcpy(status_bar_template,
           "status: Line: %4u Column: %3u                         -- %s --             ");

    gen_status_bar(status_bar);

    if (cur_file_name[0] == 0)
        strcat(title_bar, "New File");
    else
        strcat(title_bar, cur_file_name);

    printf("\n");
    printf(CLEAR);

    //Line 1
    printf(L_CYAN);
    printf("%s", title_bar);
    printf(NONE);
    printf("\n");

    //Line 2
    printf(L_GREEN);
    printf("%s", menu_bar);
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
    printf("%s", status_bar);
    printf(NONE);

    set_cursor_pos(cur_column, cur_line + 2);

    return 0;
}

int gen_status_bar(char *status_bar)
{
    unsigned int a_line = 0;
    unsigned int a_column = 0;

    a_line = cur_top + cur_line - 1;
    a_column = cur_left + cur_column - 1;

    switch (mode_flag)
    {
        case NORMAL_MODE:
            //This usage is dangerous!!
            sprintf(status_bar, status_bar_template, a_line, a_column, NORMAL);
            break;

        case INSERT_MODE:
            sprintf(status_bar, status_bar_template, a_line, a_column, INSERT);
            break;

        default:
            break;
    }
    return 0;
}

//repeat can be assigned to minus number to perform rolling left.
//return -1 for error.
//return number of units actually rolled.
int roll_rightward(int repeat)
{
    cur_left += repeat;
    return -1;
}

int roll_downward(int repeat)
{
    cur_top -= repeat;
    return -1;
}

//set cursor position to the assigned pos.
//relative to the actually console pos.
int set_cursor_pos(int x, int y)
{
    printf("\33[%d;%dH", y, x);
    return 0;
}

