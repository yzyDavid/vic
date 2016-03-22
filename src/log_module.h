//
// Created by yzy on 3/15/16.
//

#ifndef VIC_LOG_MODULE_H
#define VIC_LOG_MODULE_H

#define VIC_LOG_ON
//#undef VIC_LOG_ON

#ifdef VIC_LOG_ON
#define print_log(content) __vic_log_output(content)
#define init_log() __vic_init_log()
#pragma message("debug log enabled")
#else
#define print_log(content)
#define init_log()
#pragma message("debug log disabled")
#endif

#include <stdio.h>

extern char *log_file_name;
extern FILE *log_file_struct;

int __vic_log_output(char *content);

int __vic_init_log();

#endif //VIC_LOG_MODULE_H
