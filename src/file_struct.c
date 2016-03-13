//
// Created by yzy on 3/12/16.
// This file defines the data structure storage the lines of text.
//

#include <stdlib.h>
#include "file_struct.h"

int changed_flag = UNCHANGED;

v_file_text *cur_file;
char cur_file_name[300];

//use this function tp make sure wrong pointer isn't used.
v_line *get_line(v_file_text *file, unsigned int line)
{
    v_line *current_line = file->head;
    for (int i = 0; i < line - 1; i++)
    {
        current_line = current_line->next;
        if (current_line == NULL)
        {
            return 0;
        }
    }
    return current_line;
}

int get_char(v_line *line, unsigned int position)
{
    return line->text[position - 1];
}

int get_total_lines(v_file_text *file)
{
    v_line *current_line = file->head;
    int count = 0;
    while (current_line != NULL)
    {
        count++;
        current_line = current_line->next;
    }
    return count;
}

size_t get_length(v_line *line)
{
    return strlen((const char *) line->text);
}

