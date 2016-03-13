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
    int ch;
    v_line *cur_line;
    int *cur_char;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        return -1;
    }

//    file_struct = malloc(sizeof(v_file_text));
    file_struct->head = malloc(sizeof(v_line));
    cur_line = file_struct->head;
    cur_char = cur_line->text;
    cur_line->next = NULL;

    while ((ch = fgetc(fp)) != EOF)
    {
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
//    int ch;
    v_line *cur_line;
    int *cur_char;

    if ((fp = fopen(filename, "w")) == NULL)
    {
        return -1;
    }

    cur_line = file_struct->head;
    cur_char = cur_line->text;
    do
    {
        while (cur_char)
        {
            fputc(*cur_char, fp);
            cur_char++;
        }
        fputc('\n', fp);
    }
    while (cur_line->next != NULL);
    fclose(fp);
    return 0;
}

int v_new_file(v_file_text *file_struct)
{
    file_struct->head = malloc(sizeof(v_line));
    file_struct->head->text[0] = 0;
    return 0;
}