//
// Created by yzy on 3/15/16.
//

#include <stdio.h>
#include "log_module.h"

char *log_file_name = "vic_log.txt";
FILE *log_file_struct = NULL;

int __vic_log_output(char *content)
{
    return fprintf(log_file_struct, "%s\n", content);
}

int __vic_init_log()
{
    log_file_struct = fopen(log_file_name, "w");
    if (log_file_struct != NULL)
    {
        return 0;
    }
    return -1;
}
