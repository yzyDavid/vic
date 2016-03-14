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
    if (line == NULL)
    {
        return 0;
    }
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

int split_line(v_file_text *file_struct, unsigned int line_to_split, unsigned int index_of_start_newline)
{
    v_line *this_line = NULL;
    this_line = get_line(file_struct, line_to_split);
    unsigned int length = get_length(this_line);
    if (length < index_of_start_newline)
    {
        return -1;
    }
    v_line *new_line = create_empty_line();
    if (new_line == NULL)
    {
        return -1;
    }
    strcpy(new_line->text, this_line->text + index_of_start_newline);
    this_line->text[index_of_start_newline] = 0;
    v_line *temp = this_line->next;
    this_line->next = new_line;
    new_line->next = temp;
    return 0;
}

v_line *create_empty_line()
{
    v_line *to_create = NULL;
    to_create = malloc(sizeof(v_line));
    to_create->text[0] = 0;
    return to_create;
}

int insert_empty_line(v_file_text *file_struct, unsigned int line_to_insert_after)
{
    v_line *line_before = get_line(file_struct, line_to_insert_after);
    v_line *temp = line_before->next;
    v_line *new_line = create_empty_line();
    if (new_line == NULL)
    {
        return -1;
    }
    new_line->next = temp;
    line_before->next = new_line;
    return 0;
}

unsigned int count_ltrim_space(v_line *line)
{
    unsigned int i = 0;
    unsigned int length = get_length(line);

    for (; i < length; i++)
    {
        if (line->text[i] != ' ')
        {
            return i;
        }
    }
    return (unsigned int)-1;
}

