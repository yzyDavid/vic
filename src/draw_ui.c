//
// Created by yzy on 3/12/16.
//
#include "main.h"

#ifdef __VIC_POSIX

#include <sys/ioctl.h>

#endif

#ifdef __VIC_WIN

#include <windows.h>

#define BACKGROUND_INTENSITY 0

#endif

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>

#include "draw_ui.h"
#include "file_struct.h"
#include "main_loop.h"
#include "termios_set.h"
#include "bottomline_loop.h"

//This globals defines the position of "cursor".
//relative to the line3-23 (actually contains the file) part.
unsigned int cur_line;
unsigned int cur_column;

//This globals defines the position of the screen.
//relative to the file.
unsigned int cur_top;
unsigned int cur_left;

//The lines and columns of the console window.
unsigned int console_lines = CONSOLE_LINES;
unsigned int console_columns = CONSOLE_COLUMNS;

//The lines and columns of the text area.
unsigned int screen_lines = SCREEN_LINES;
unsigned int screen_columns = SCREEN_COLUMNS;

char title_bar[CONSOLE_COLUMNS + 1];
char menu_bar[CONSOLE_COLUMNS + 1];
char status_bar[CONSOLE_COLUMNS + 1];
char status_bar_template[CONSOLE_COLUMNS + 1];

//The string length should be checked by bottomline mode loop.
char bottomline_text[CONSOLE_COLUMNS + 1];

#ifdef __VIC_POSIX
int __redraw_ui_posix()
{
    console_lines = get_terminal_lines();
    console_columns = get_terminal_columns();
    screen_lines = console_lines - 3;
    screen_columns = console_columns;

    strcpy(title_bar,
           "vic - ");
    strcpy(menu_bar,
           "New File[1,n] Save[2,s]                                --  menu  --");
    strcpy(status_bar_template,
           "status: Line: %4u Column: %4u                        -- %s --");

    gen_status_bar(status_bar);

    if (cur_file_name[0] == 0)
    {
        strcat(title_bar, "New File");
    }
    else
    {
        strcat(title_bar, cur_file_name);
    }

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
    for (int i = 0; i < screen_lines; i++)
    {
        int finished_flag = 0;
        v_line *current_line = get_line(cur_file, i + cur_top);
        if (current_line != NULL)
        {
            for (int j = 0; j < screen_columns; j++)
            {
                if (finished_flag || current_line->text[cur_left + j - 1] == 0)
                {
                    finished_flag = 1;
                    printf(" ");
                }
                else
                {
                    if (current_line->info[cur_left + j - 1] == KEYWORD)
                    {
                        printf(YELLOW);
                    }
                    printf("%c", current_line->text[cur_left + j - 1]);
                    if (current_line->info[cur_left + j - 1] == KEYWORD)
                    {
                        printf(NONE);
                    }
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
#endif

int gen_status_bar(char *status_bar)
{
    unsigned int a_line = 0;
    unsigned int a_column = 0;

    a_line = cur_top + cur_line - 1;
    a_column = cur_left + cur_column - 1;

    if (changed_flag == UNSAVED)
    {
        sprintf(status_bar, status_bar_template, a_line, a_column, SAVE_WARN);
        return 0;
    }

    switch (mode_flag)
    {
        case NORMAL_MODE:
            //This usage is dangerous!!
            sprintf(status_bar, status_bar_template, a_line, a_column, NORMAL);
            break;

        case INSERT_MODE:
            sprintf(status_bar, status_bar_template, a_line, a_column, INSERT);
            break;

        case BOTTOMLINE_MODE:
            switch (bottomline_sub_mode)
            {
                case BOTTOM_LINE_FILENAME:
                    sprintf(status_bar, ":%s", bottomline_text);
                    break;

                case BOTTOM_LINE_SEARCH:
                    sprintf(status_bar, "/%s", bottomline_text);
                    break;

                default:
                    sprintf(status_bar, "%s", bottomline_text);
                    break;
            }
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
    cur_top += repeat;
    return -1;
}

//set cursor position to the assigned pos.
//relative to the actually console pos.
#ifdef __VIC_POSIX

int __set_cursor_pos_posix(int x, int y)
{
    printf("\33[%d;%dH", y, x);
    return 0;
}

unsigned int __get_terminal_lines_posix()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
}

unsigned int __get_terminal_columns_posix()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

#endif

#ifdef __VIC_WIN

int __redraw_ui_win()
{
    console_lines = get_terminal_lines();
    console_columns = get_terminal_columns();
    screen_lines = console_lines - 3;
    screen_columns = console_columns;

    strcpy(title_bar,
           "vic - ");
    strcpy(menu_bar,
           "New File[1,n] Save[2,s]                                --  menu  --");
    strcpy(status_bar_template,
           "status: Line: %4u Column: %4u                        -- %s --");

    gen_status_bar(status_bar);

    if (cur_file_name[0] == 0)
    {
        strcat(title_bar, "New File");
    }
    else
    {
        strcat(title_bar, cur_file_name);
    }

    system("CLS");

    //Line 1:
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
    printf("%s", title_bar);
    printf("\n");

    //Line 2:
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
    printf("%s", menu_bar);
    printf("\n");

    //Belows are file content area.
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_INTENSITY);

    for (int i = 0; i < screen_lines; i++)
    {
        int finished_flag = 0;
        v_line *current_line = get_line(cur_file, i + cur_top);
        if (current_line != NULL)
        {
            for (int j = 0; j < screen_columns; j++)
            {
                if (finished_flag || current_line->text[cur_left + j - 1] == 0)
                {
                    finished_flag = 1;
                    printf(" ");
                }
                else
                {
                    if (current_line->info[cur_left + j - 1] == KEYWORD)
                    {
                        SetConsoleTextAttribute(hStdOut,
                                                FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
                    }
                    printf("%c", current_line->text[cur_left + j - 1]);
                    if (current_line->info[cur_left + j - 1] == KEYWORD)
                    {
                        SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED |
                                                         BACKGROUND_INTENSITY);
                    }
                }
            }
        }
        printf("\n");
    }

    //Line status bar.
    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
    printf("%s", status_bar);
    SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_INTENSITY);

    set_cursor_pos(cur_column - 1, cur_line + 2 - 1);

    return 0;
}

int __set_cursor_pos_win(int x, int y)
{
    COORD cur_pos;
    cur_pos.X = (SHORT) x;
    cur_pos.Y = (SHORT) y;
    SetConsoleCursorPosition(hStdOut, cur_pos);
    return 0;
}

//return 0 as error.
unsigned int __get_terminal_lines_win()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hStdOut, &info);
    return (unsigned int) info.srWindow.Bottom - info.srWindow.Top;
}

//return 0 as error.
unsigned int __get_terminal_columns_win()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hStdOut, &info);
    return (unsigned int) info.srWindow.Right - info.srWindow.Left;
}

//Not in use.
int __set_text_color_win()
{
    return -1;
}

#endif

