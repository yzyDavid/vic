//
// Created by yzy on 3/12/16.
//

/*
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
 */

#ifndef VIC_DRAW_UI_H
#define VIC_DRAW_UI_H

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

int redraw_ui();

extern char title_bar[CONSOLE_COLUMNS + 1];
extern char menu_bar[CONSOLE_COLUMNS + 1];
extern char status_bar[CONSOLE_COLUMNS + 1];

#define SCREEN_LINES 21
#define SCREEN_COLUMNS 80

#define NORMAL "NORMAL"
#define INSERT "INSERT"
#define SAVE_WARN "!SAVE!"

int gen_status_bar(char *status_bar);

int roll_rightward(int repeat);
int roll_downward(int repeat);

int set_cursor_pos(int x, int y);

extern unsigned int cur_line;
extern unsigned int cur_column;

extern unsigned int cur_top;
extern unsigned int cur_left;

#endif //VIC_DRAW_UI_H

/*
#pragma clang diagnostic pop
 */