/*
 *    This file is used for test purposes.
 */
#include <unistd.h>
#include <termios.h>
#include <stdio.h>

#include "printf_color.h"

int main()
{
    printf_color();
    int input;

    struct termios save, current;
    tcgetattr(0, &save);
    current = save;
    current.c_lflag &= ~ICANON;
    current.c_lflag &= ~ECHO;
    current.c_cc[VMIN] = 1;
    current.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &current);

    printf("input your data:\n");
    while ((input = getchar()) != 'q')
    {
        printf("input=%c\n", input);
    }

    tcsetattr(0, TCSANOW, &save);

    return 0;
}