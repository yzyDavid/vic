//
// Created by yzy on 3/21/2016.
//

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 100;
    while (i--)
    {
        printf("%x\n", getch());
        printf("%x\n", (char) (0xe0 & 0xff));
        /*
        switch (getch())
        {
            default:
                break;
            case '\xe0':
                if (getch() == '\x48')
                    printf("up\n");
                break;
        }
         */
    }
    return 0;
}
