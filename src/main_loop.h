//
// Created by yzy on 3/12/16.
//

#ifndef VIC_MAIN_LOOP_H
#define VIC_MAIN_LOOP_H

#define NORMAL_MODE 0
#define INSERT_MODE 1
#define REWRITE_MODE 2
#define BOTTOMLINE_MODE 3

extern int mode_flag;

int main_loop();

int cursor_left();
int cursor_right();
int cursor_up();
int cursor_down();

int goto_line_end();

int is_position_in_file();

#endif //VIC_MAIN_LOOP_H
