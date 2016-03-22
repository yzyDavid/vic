//
// Created by yzy on 3/18/16.
//

#ifndef VIC_BOTTOMLINE_LOOP_H
#define VIC_BOTTOMLINE_LOOP_H

#define BOTTOM_LINE_EXCEPT 0
#define BOTTOM_LINE_FILENAME_SAVE 1
#define BOTTOM_LINE_SEARCH 2
#define BOTTOM_LINE_FILENAME_OPEN 3

extern int bottomline_sub_mode;

int bottomline_mode_process(int key_down);

#endif //VIC_BOTTOMLINE_LOOP_H
