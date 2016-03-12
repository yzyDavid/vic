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
    v_line *cur_line = file->head;
    for (int i = 0; i < line - 1; i++)
    {
        cur_line = cur_line->next;
        if (cur_line == NULL)
        {
            return 0;
        }
    }
    return cur_line;
}

int get_char(v_line *line, unsigned int position)
{
    return line->text[position - 1];
}
