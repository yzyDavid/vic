//
// Created by yzy on 3/12/16.
//
#include <stdio.h>
#include <stdlib.h>

#include "file_sl.h"
#include "lines_list.h"

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

    file_struct = malloc(sizeof(v_file_text));
    file_struct->head = malloc(sizeof(v_line));
    cur_line = file_struct->head;
    cur_char = cur_line->text;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch != '\n')
        {

        }
        else
        {

        }
    }

    fclose(fp);
}

int v_save_file(const char *filename, v_file_text *file_struct)
{

}