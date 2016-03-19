//
// Created by yzy on 3/12/16.
//

/*
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
 */

#ifndef VIC_DRAW_UI_H
#define VIC_DRAW_UI_H

#include "main.h"

//constants below are default lines or columns of the console.
#define CONSOLE_LINES 24
#define CONSOLE_COLUMNS 80

/*Use
 * man console_codes
 * to show the declare of params below.
 */
#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"

#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J"
#define CLRLINE              "\r\e[K" //or "\e[1K\r"

#define HIDE_CURSOR     "\e[?25l"
#define SHOW_CURSOR     "\e[?25h"

#ifdef __VIC_POSIX
#define redraw_ui __redraw_ui_posix
#define get_terminal_columns __get_terminal_columns_posix
#define get_terminal_lines __get_terminal_lines_posix
#define set_cursor_pos __set_cursor_pos_posix
#endif

#ifdef __VIC_WIN
#define redraw_ui __redraw_ui_win
#define get_terminal_columns __get_terminal_columns_win
#define get_terminal_lines __get_terminal_lines_win
#define set_cursor_pos __set_cursor_pos_win
#endif

extern unsigned int screen_lines;
extern unsigned int screen_columns;

extern unsigned int console_lines;
extern unsigned int console_columns;

#ifdef __VIC_POSIX
int __redraw_ui_posix();

unsigned int __get_terminal_columns_posix();

unsigned int __get_terminal_lines_posix();
#endif

#ifdef __VIC_WIN
int __redraw_ui_win();
#endif

extern char title_bar[CONSOLE_COLUMNS + 1];
extern char menu_bar[CONSOLE_COLUMNS + 1];
extern char status_bar[CONSOLE_COLUMNS + 1];
extern char bottomline_text[CONSOLE_COLUMNS + 1];

//defines default lines and columns for text area.
#define SCREEN_LINES (CONSOLE_LINES - 3)
#define SCREEN_COLUMNS CONSOLE_COLUMNS

#define NORMAL "NORMAL"
#define INSERT "INSERT"
#define SAVE_WARN "!SAVE!"

int gen_status_bar(char *status_bar);

int roll_rightward(int repeat);

int roll_downward(int repeat);

#ifdef __VIC_POSIX
int __set_cursor_pos_posix(int x, int y);
#endif

extern unsigned int cur_line;
extern unsigned int cur_column;

extern unsigned int cur_top;
extern unsigned int cur_left;

#endif //VIC_DRAW_UI_H

/*
#pragma clang diagnostic pop
 */