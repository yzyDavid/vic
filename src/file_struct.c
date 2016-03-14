//
// Created by yzy on 3/12/16.
// This file defines the data structure storage the lines of text.
//

#include <stdlib.h>
#include <string.h>
#include "file_struct.h"
#include "highlight.h"

int changed_flag = UNCHANGED;

v_file_text *cur_file;
char cur_file_name[FILE_LINE_LENGTH];

//use this function tp make sure wrong pointer isn't used.
v_line *get_line(v_file_text *file, unsigned int line)
{
    v_line *current_line = file->head;
    for (int i = 0; i < line - 1; i++)
    {
        current_line = current_line->next;
        if (current_line == NULL)
        {
            return NULL;
        }
    }
    return current_line;
}

int get_char(v_line *line, unsigned int position)
{
    return line->text[position - 1];
}

unsigned int get_total_lines(v_file_text *file)
{
    v_line *current_line = file->head;
    unsigned int count = 0;
    while (current_line != NULL)
    {
        count++;
        current_line = current_line->next;
    }
    return count;
}

unsigned int get_length(v_line *line)
{
    size_t length = strlen(line->text);
    return (unsigned int) length;
}

//find a whole word
//start is relative to the actual position (1 is the first index).
//return the index of end char in the array.
//return 0 on failed.
unsigned int judge_word(v_line *line, unsigned int start)
{
    unsigned int length = get_length(line);
    unsigned int i;
    char *j = NULL;
    int flag = 0;
    for (i = start; i < length; i++)
    {
        flag = 0;
        for (j = word_char_list; *j != 0; j++)
        {
            if (*j == line->text[i])
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            goto judge_word_success;
        }
    }
    return 0;
    judge_word_success:
    return i - 1;
}
