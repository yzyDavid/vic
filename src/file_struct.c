//
// Created by yzy on 3/12/16.
// This file defines the data structure storage the lines of text.
//

#include <stdlib.h>
#include <string.h>
#include "file_struct.h"
#include "highlight.h"
#include "log_module.h"

int changed_flag = UNCHANGED;

v_file_text *cur_file;
char cur_file_name[FILE_LINE_LENGTH];
int cur_file_type = PLAIN_TEXT;

//use this function tp make sure wrong pointer isn't used.
//line is start from 1
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
    return (unsigned int) -1;
}

int parse_highlighting(v_file_text *file_struct)
{
    int i, j, k;
    int lines = get_total_lines(cur_file);
    char **highlight_list;
    char word_temp[FILE_LINE_LENGTH];
    switch (cur_file_type)
    {
        case C_SOURCE:
            highlight_list = c_highlight_list;
            break;

        case CPLUSPLUS_SOURCE:
            highlight_list = cplusplus_highlight_list;
            break;

        default:
//            return -1;
            highlight_list = c_highlight_list;
    }
    for (i = 0; i < lines; i++)
    {
        v_line *line_processing = get_line(file_struct, (unsigned int) (i + 1));
        int length = get_length(line_processing);
        for (j = 0; j < length; j++)
        {
            if (j != 0 && !is_word_start(line_processing->text + j))
            {
                continue;
            }
            line_processing->info[j] = COMMON_TEXT;
            int end = judge_word(line_processing, (unsigned int) (j + 1));
            if (end != 0)
            {
                memset(word_temp, 0, sizeof(word_temp));
                strncpy(word_temp, line_processing->text + j, (size_t) (end - j + 1));
                print_log(word_temp);
            }
            for (k = 0; *(highlight_list[k]) != 0; k++)
            {
                if ((strcmp(highlight_list[k], word_temp) == 0))
                {
                    for (int t = j; t <= end; t++)
                    {
                        line_processing->info[t] = KEYWORD;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}

int determine_file_type(char *file_name)
{
    unsigned length = (unsigned int) strlen(file_name);
    if (strcmp(file_name + length - 2, ".c") == 0)
    {
        cur_file_type = C_SOURCE;
        return 0;
    }
    if (strcmp(file_name + length - 2, ".C") == 0)
    {
        cur_file_type = C_SOURCE;
        return 0;
    }
    if (strcmp(file_name + length - 4, ".cpp") == 0)
    {
        cur_file_type = CPLUSPLUS_SOURCE;
        return 0;
    }
    if (strcmp(file_name + length - 3, ".cc") == 0)
    {
        cur_file_type = CPLUSPLUS_SOURCE;
        return 0;
    }
    if (strcmp(file_name + length - 4, ".cxx") == 0)
    {
        cur_file_type = CPLUSPLUS_SOURCE;
        return 0;
    }
    if (strcmp(file_name + length - 4, ".CPP") == 0)
    {
        cur_file_type = CPLUSPLUS_SOURCE;
        return 0;
    }

    return 0;
}

//caution!! this function check place before the pointer place!!
int is_word_start(char *place)
{
    if (*(place - 1) != ' ')
    {
        return 0;
    }
    for (char *i = word_char_list; *i != 0; i++)
    {
        if (*place == *i)
        {
            return 1;
        }
    }
    return 0;
}