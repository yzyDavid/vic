//
// Created by yzy on 3/12/16.
// This file defines the data structure storage the lines of text.
//

#ifndef VIC_LINES_LIST_H
#define VIC_LINES_LIST_H

#define LINE_LENGTH 300

typedef struct v_line_s {
    char text[LINE_LENGTH];
    struct v_line_s *next;
} v_line;

typedef struct {
    v_line *head;
} v_file_text;

#endif //VIC_LINES_LIST_H
