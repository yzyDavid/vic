//
// Created by yzy on 3/12/16.
// This file defines the data structure storage the lines of text.
//

#ifndef VIC_LINES_LIST_H
#define VIC_LINES_LIST_H

#include <string.h>

#define LINE_LENGTH (1024*16)

#define FILE_LINE_LENGTH (1024*4)

//save status macro
#define UNCHANGED 0
#define CHANGED 1
#define UNSAVED 2

//highlighting info constants
#define COMMON_TEXT 0
#define KEYWORD 1
#define STRING 2
#define COMMENT 3

//file type constants
#define PLAIN_TEXT 0
#define C_SOURCE 1
#define CPLUSPLUS_SOURCE 2

extern int changed_flag;

extern char cur_file_name[FILE_LINE_LENGTH];

extern int cur_file_type;

typedef struct v_line_s
{
    char text[LINE_LENGTH];
    char info[LINE_LENGTH];
    struct v_line_s *next;
} v_line;

typedef struct v_file_text_s
{
    v_line *head;
} v_file_text;

extern v_file_text *cur_file;

v_line *get_line(v_file_text *file, unsigned int line);

int get_char(v_line *line, unsigned int position);

unsigned int get_total_lines(v_file_text *file);

unsigned int get_length(v_line *line);

unsigned int judge_word(v_line *line, unsigned int start);

int split_line(v_file_text *file_struct, unsigned int line_to_split, unsigned int index_of_start_newline);

v_line *create_empty_line();

int insert_empty_line(v_file_text *file_struct, unsigned int line_to_insert_after);

unsigned int count_ltrim_space(v_line *line);

int is_word_start(char *place);

int parse_highlighting(v_file_text *file_struct);

int determine_file_type(char *file_name);

#endif //VIC_LINES_LIST_H

