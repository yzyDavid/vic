//
// Created by yzy on 3/13/16.
//

#include <assert.h>
#include <stdlib.h>

#include "normal_loop.h"
#include "file_struct.h"
#include "draw_ui.h"
#include "main_loop.h"
#include "termios_set.h"
#include "file_sl.h"

int normal_mode_process(int key_down)
{
    int second_key_down = 0;
    switch (key_down)
    {
        case '\x1b':  //Esc
#ifdef __VIC_POSIX
            second_key_down = getchar();
#endif
            switch (second_key_down)    //double stroke Esc to return to normal mode.
            {
                case '\x5b':
#ifdef __VIC_POSIX
                    second_key_down = getchar();
#endif
                    switch (second_key_down)
                    {
                        case '\x41':     //up
                            cursor_up();
                            break;

                        case '\x42':     //down
                            cursor_down();
                            break;

                        case '\x43':     //right
                            cursor_right();
                            break;

                        case '\x44':     //left
                            cursor_left();
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            break;

        case '!':   //quit directly.
            enable_display_back();
            set_cursor_pos(console_columns, console_lines);
            exit(0);
            break;

        case '1':   //New File.
            if (changed_flag == UNCHANGED || changed_flag == UNSAVED)
            {
                enable_display_back();
                set_cursor_pos(console_columns, console_lines);
            }
            else
            {
                changed_flag = UNSAVED;
            }
            break;

        case 'q':   //quit, is saved should be checked.
            if (changed_flag == UNCHANGED || changed_flag == UNSAVED)
            {
                enable_display_back();
                set_cursor_pos(console_columns, console_lines);
                exit(0);
            }
            else
            {
                changed_flag = UNSAVED;
            }
            break;

            //belows hjkl for cursor moving.
            //aiming to disable moving cursor outside the file part.
        case 'h':
            cursor_left();
            break;

        case 'l':
            cursor_right();
            break;

        case 'j':
            cursor_down();
            break;

        case 'k':
            cursor_up();
            break;

        case 'w':   //word forward.
        {
            int position = cur_left + cur_column - 1;
            int counter = 0;
            char *cur = get_line(cur_file, cur_top + cur_line - 1)->text;
            cur += cur_left + cur_column - 2;   //to be checked.
            if (is_word_start(cur))
            {
                position++;
                counter++;
                cur++;
            }
            for (; position < get_length(get_line(cur_file, cur_line + cur_top - 1)); position++, counter++)
            {
                if (is_word_start(cur++))
                {
                    break;
                }
            }
            for (; counter > 0; counter--)
            {
                cursor_right();
            }
        }
            break;

        case 'b':   //word backward.
        {
            int position = cur_left + cur_column - 1;
            int counter = 0;
            char *cur = get_line(cur_file, cur_top + cur_line - 1)->text;
            cur += cur_left + cur_column - 2;   //to be checked.
            if (is_word_start(cur))
            {
                position--;
                counter++;
                cur--;
            }
            for (; position > 0; position--, counter++)
            {
                if (is_word_start(cur--))
                {
                    break;
                }
            }
            for (; counter > 0; counter--)
            {
                cursor_left();
            }
        }
            break;

        case 'e':   //word-end forward.
            break;

        case 'i':   //insert.
            mode_flag = INSERT_MODE;
            break;

        case 'a':   //append.
            cursor_right();
            mode_flag = INSERT_MODE;
            break;

        case 'd':   //delete a word.
        {
            v_line *this_line = get_line(cur_file, cur_top + cur_line - 1);
            unsigned int word_len = 0;
            unsigned int start_index = cur_left + cur_column - 2;
            unsigned int end_index = judge_word(this_line, start_index + 1);
            word_len = end_index - start_index + 1;
            for (int i = 0; i < end_index - start_index + 1; i++)
            {
                del_char(this_line, cur_left + cur_column - 2);
            }
            if (word_len != 0)
            {
                changed_flag = CHANGED;
            }
        }
            break;

        case 'x':   //delete a single char.
            del_char(get_line(cur_file, cur_top + cur_line - 1), cur_left + cur_column - 2);
            changed_flag = CHANGED;
            break;

        case 'o':   //open new line.
            insert_empty_line(cur_file, cur_top + cur_line - 1);
            cursor_down();
            mode_flag = INSERT_MODE;
            break;

        case '$':
            goto_line_end();
            break;

        case '^':   //goto first char of line.
            goto_line_actual_start();
            break;

        case '0':   //goto fixed first column.
            goto_line_start();
            break;

        case ':':   //bottom line command mode.
            break;

        case '/':    //bottom line and search.
            break;

        case '2':
        case 's':
            v_save_file(cur_file_name, cur_file);
            changed_flag = UNCHANGED;
            break;

        default:
            break;
    }
    return 0;
}


//functions below is the implements of moving the cursor.
//only should be called when its under normal or insert mode.
//return code:
//0: move failed.
//1: move success.
//-1: exceptions.
int cursor_left()
{
    unsigned int lines;
    lines = get_total_lines(cur_file);
    if (cur_column == 1 && cur_left == 1)
    {
        return 0;
    }
    cur_column--;
    if (!is_position_in_file())
    {
        if (cur_line + cur_top - 1 <= lines)
        {
            return 1;
        }
        cur_column++;
        return 0;
    }
    else if (cur_column > 1)
    {
        return 1;
    }
    else if (cur_left > 1)
    {
        cur_column++;
        roll_rightward(-1);
        return 1;
    }
    return -1;
}

int cursor_right()
{
    assert(cur_column <= screen_columns);
    ++cur_column;
    if (!is_position_in_file())
    {
        cur_column--;
        return 0;
    }
    else if (cur_column >= screen_columns)
    {
        --cur_column;
        roll_rightward(1);
        return 1;
    }
    else
    {
        return 1;
    }
    return -1;
}

int cursor_up()
{
    unsigned int length = 0;
    if (cur_line == 1 && cur_top == 1)
    {
        return 0;
    }
    else if (cur_line > 1)
    {
        cur_line--;
        length = (int) strlen((const char *) get_line(cur_file, cur_line + cur_top - 1));
//        length = (length == 0) ? 1 : length;
        if (length < cur_column)
        {
            cur_column = length;
            cur_column = (cur_column == 0) ? 1 : cur_column;
        }
        return 1;
    }
    else if (cur_top > 1)
    {
        roll_downward(-1);
        return 1;
    }
    return -1;
}

//Have bugs in calc position.
// test data:
// cur_left     21
// cur_column   80
// length       0
//
//another group crash data:
//cur_left      1
//cur_column    1
//length        0

//return code:
//0: move failed.
//1: move success.
//-1: exceptions.
int cursor_down()
{
    unsigned int length = 0;
    unsigned int lines = 0;
    unsigned int actual_column = 0;

    lines = get_total_lines(cur_file);
    cur_line++;

    if (cur_top + cur_line - 1 > lines)
    {
        cur_line--;
        return 0;
    }

    length = (unsigned int) strlen((const char *) get_line(cur_file, cur_line + cur_top - 1));
    actual_column = cur_left + cur_column - 1;

    if (is_position_in_file())
    {
        if (cur_line > screen_lines)
        {
            cur_line--;
            roll_downward(1);
            return 1;
        }
        else
        {
            return 1;
        }
    }
    else    //is_position_in_file = false
    {
        if (cur_line + cur_top - 1 <= lines)   //not exceed the lines EOF
        {
            if (cur_line > screen_lines)
            {
                cur_line--;
                roll_downward(1);
            }

//            assert(length != 0);
//            assert(actual_column > length);
            //length = cur_left + cur_column - 1

            // decline if the end of line outside the screen.
            if (length == 0)
            {
                cur_left = 1;
                cur_column = 1;
                return 1;
            }
            if (cur_left <= length)
            {
                cur_column = length - cur_left + 1;
                cur_column = (cur_column == 0) ? 1 : cur_column;
                return 1;
            }
            else
            {
                cur_column = screen_columns;
                cur_left = length - cur_column + 1;
                return 1;
            }
        }
        else    //exceed EOF lines
        {
            cur_line--;
            return 0;
        }
    }

    assert(-1);
    return -1;
}

int goto_line_end()
{
    unsigned int actual_column = 0;
    unsigned int length = 0;
    length = (unsigned int) strlen((const char *) get_line(cur_file, cur_line + cur_top - 1));
//    length = (length == 0) ? 1 : length;
    actual_column = cur_left + cur_column - 1;
    if (length > actual_column)
    {
        for (int i = 0; i < length - actual_column; i++)
        {
            cursor_right();
        }
    }
    else
    {
        for (int i = 0; i < actual_column - length; i++)
        {
            cursor_left();
        }
    }
    return 0;
}

int goto_line_start()
{
    unsigned int actual_column = 0;
    actual_column = cur_left + cur_column - 1;
    for (int i = 0; i < actual_column - 1; i++)
    {
        cursor_left();
    }

    return 0;
}

int goto_line_actual_start()
{
    unsigned int actual_column = 0;
    actual_column = cur_left + cur_column - 1;
    unsigned int repeat = actual_column - 1;
    unsigned length = get_length(get_line(cur_file, cur_top + cur_line - 1));
    char *pos = get_line(cur_file, cur_top + cur_line - 1)->text;
    while (repeat > 0)
    {
        if (*pos++ == ' ')
        {
            repeat--;
        }
        else
        {
            break;
        }
    }
    for (int i = 0; i < repeat; i++)
    {
        cursor_left();
    }
    return 0;
}


