//
// Created by yzy on 3/12/16.
// This file defines the data structure storage the lines of text.
//

#ifndef VIC_LINES_LIST_H
#define VIC_LINES_LIST_H

#include <string.h>

#define LINE_LENGTH 300

#define UNCHANGED 0
#define CHANGED 1

#define FILE_LINE_LENGTH 900

extern int changed_flag;

extern char cur_file_name[FILE_LINE_LENGTH];

typedef struct v_line_s
{
    char text[LINE_LENGTH];
    struct v_line_s *next;
} v_line;

typedef struct
{
    v_line *head;
} v_file_text;

extern v_file_text *cur_file;

v_line *get_line(v_file_text *file, unsigned int line);

int get_char(v_line *line, unsigned int position);

unsigned int get_total_lines(v_file_text *file);

unsigned int get_length(v_line *line);

unsigned int judge_word(v_line *line, unsigned int start);

#endif //VIC_LINES_LIST_H
