//
// Created by yzy on 3/12/16.
// This file defines the data structure storage the lines of text.
//

#ifndef VIC_LINES_LIST_H
#define VIC_LINES_LIST_H

#define LINE_LENGTH 300

extern char cur_file_name[300];

typedef struct v_line_s {
    int text[LINE_LENGTH];
    struct v_line_s *next;
} v_line;

typedef struct {
    v_line *head;
} v_file_text;

extern v_file_text cur_file;

#endif //VIC_LINES_LIST_H
