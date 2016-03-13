//
// Created by yzy on 3/12/16.
//

#ifndef VIC_FILE_SL_H
#define VIC_FILE_SL_H

#include "file_struct.h"

int v_load_file(const char *filename, v_file_text *);

int v_save_file(const char *filename, v_file_text *);

int v_new_file(v_file_text *file_struct);

int add_char(v_file_text *file_struct, unsigned int line, unsigned int position, char char_to_add);

#endif //VIC_FILE_SL_H
