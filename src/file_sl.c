//
// Created by yzy on 3/12/16.
//
#include <stdio.h>
#include <stdlib.h>

#include "file_sl.h"
#include "file_struct.h"

//This program convert all the tabs to 4 spaces.

int v_load_file(const char *filename, v_file_text *file_struct)
{
    FILE *fp;
    char ch;
    v_line *cur_line;
    char *cur_char;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        return -1;
    }

//    file_struct = malloc(sizeof(v_file_text));
    file_struct->head = malloc(sizeof(v_line));
    cur_line = file_struct->head;
    cur_char = cur_line->text;
    cur_line->next = NULL;

    while ((ch = (char) fgetc(fp)) != EOF)
    {
        if (ch == '\r')
        {
            continue;
        }

        if (ch != '\n')
        {
            if (ch == '\t')
            {
                *cur_char = ' ';
                cur_char++;
                *cur_char = ' ';
                cur_char++;
                *cur_char = ' ';
                cur_char++;
                *cur_char = ' ';
                cur_char++;
            }
            else
            {
                *cur_char = ch;
                cur_char++;
            }
        }
        else
        {
            cur_line->next = malloc(sizeof(v_line));
            cur_line = cur_line->next;
            cur_line->next = NULL;
            memset(cur_line->text, 0, FILE_LINE_LENGTH);
            *cur_char = 0;
            cur_char = cur_line->text;
        }
    }

    fclose(fp);
    return 0;
}

int v_save_file(const char *filename, v_file_text *file_struct)
{
    FILE *fp;
    v_line *cur_line;
    char *cur_char;

    if (strlen(filename) == 0)
    {
        return -1;
    }

    if ((fp = fopen(filename, "w")) == NULL)
    {
        return -1;
    }

    cur_line = file_struct->head;
    cur_char = cur_line->text;
    do
    {
        while (*cur_char)
        {
            fputc(*cur_char, fp);
            cur_char++;
        }
        fputc('\n', fp);
        cur_line = cur_line->next;
        cur_char = cur_line->text;
    }
    while (NULL != cur_line);
    fclose(fp);
    return 0;
}

int v_new_file(v_file_text *file_struct)
{
    file_struct->head = malloc(sizeof(v_line));
    memset(file_struct->head->text, 0, FILE_LINE_LENGTH);
    memset(file_struct->head->info, 0, FILE_LINE_LENGTH);
    file_struct->head->next = NULL;

    return 0;
}

//This function do no safety checks!
//position start from 1.
//12340
int add_char(v_file_text *file_struct, unsigned int line, unsigned int position, char char_to_add)
{
    unsigned int length = 0;
    v_line *this_line = get_line(file_struct, line);
    length = get_length(this_line);
//    length = (length == 0) ? 1 : length;
    for (int i = ((length < LINE_LENGTH) ? length : LINE_LENGTH); i >= position; i--)
    {
        this_line->text[i] = this_line->text[i - 1];
    }
    this_line->text[position - 1] = char_to_add;
    return 0;
}

//delete a single char
//index relative to array index.
int del_char(v_line *line, unsigned int index)
{
    unsigned int length = 0;
    length = get_length(line);
    for (int i = index; i < length; i++)
    {
        line->text[i] = line->text[i + 1];
    }
    return 0;
}

//this func also freed the file_struct.
int v_free_file(v_file_text *file_struct)
{
    v_line *head = file_struct->head;
    v_line *cur = head;
    v_line *tmp = NULL;
    while (cur->next != NULL)
    {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(cur);
    free(file_struct);
    file_struct = NULL;
    return -1;
}


