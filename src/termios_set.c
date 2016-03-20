//
// Created by yzy on 3/12/16.
//This file defines functions and variables relative to platform, handling console behaviors.
//
#include "main.h"

#ifdef __VIC_POSIX
#include <termios.h>
#endif

#ifdef __VIC_WIN

#include <windows.h>
#include <wincon.h>

#endif

#include <stdio.h>
#include <afxres.h>

#include "termios_set.h"
#include "draw_ui.h"

#ifdef __VIC_POSIX
static struct termios disabled;
static struct termios enabled;
#endif

#ifdef __VIC_WIN
static HANDLE hConsole = 0;
static CONSOLE_CURSOR_INFO *pOldCurInfo;
#endif

int init_display_back()
{
#ifdef __VIC_POSIX
    tcgetattr(0, &enabled);
    disabled = enabled;
    disabled.c_lflag &= ~ICANON;
    disabled.c_lflag &= ~ECHO;
    disabled.c_cc[VMIN] = 1;
    disabled.c_cc[VTIME] = 0;
#endif

#ifdef __VIC_WIN
    pOldCurInfo = malloc(sizeof(CONSOLE_CURSOR_INFO));
    CONSOLE_CURSOR_INFO *lpConInfo = malloc(sizeof(CONSOLE_CURSOR_INFO));
    lpConInfo->bVisible = TRUE;
    lpConInfo->dwSize = 100;
    __get_self_window_win();
    GetConsoleCursorInfo(hConsole, pOldCurInfo);
    SetConsoleCursorInfo(hConsole, lpConInfo);
#endif
    return 0;
}

int disable_display_back()
{
#ifdef __VIC_POSIX
    tcsetattr(0, TCSANOW, &disabled);
#endif
    return 0;
}

int enable_display_back()
{
#ifdef __VIC_POSIX
    tcsetattr(0, TCSANOW, &enabled);
    printf(NONE);
#endif
    return 0;
}

int hide_cursor()
{
#ifdef __VIC_POSIX
    printf(HIDE_CURSOR);
#endif

#ifdef __VIC_WIN
    CONSOLE_CURSOR_INFO *lpConInfo = malloc(sizeof(CONSOLE_CURSOR_INFO));
    lpConInfo->bVisible = FALSE;
    lpConInfo->dwSize = 100;
    __get_self_window_win();
    SetConsoleCursorInfo(hConsole, lpConInfo);
#endif
    return 0;
}

int show_cursor()
{
#ifdef __VIC_POSIX
    printf(SHOW_CURSOR);
#endif

#ifdef __VIC_WIN
    CONSOLE_CURSOR_INFO *lpConInfo = malloc(sizeof(CONSOLE_CURSOR_INFO));
    lpConInfo->bVisible = TRUE;
    lpConInfo->dwSize = 100;
    __get_self_window_win();
    SetConsoleCursorInfo(hConsole, lpConInfo);
#endif
    return 0;
}

#ifdef __VIC_WIN

//This function set the global hConsole.
//Also set console title.
int __get_self_window_win()
{
    if (hConsole != 0)
    {
        return 0;
    }
    DWORD _BUFSIZE;
    _BUFSIZE = 1024;
    char pszNewWindowTitle[_BUFSIZE];

    wsprintf(pszNewWindowTitle, "%d/%d",
             GetTickCount(),
             GetCurrentProcessId());

    SetConsoleTitle(pszNewWindowTitle);

    Sleep(40);

    hConsole = FindWindow(NULL, pszNewWindowTitle);

    // Restore original window title.

    SetConsoleTitle("vic");
    return 0;
}

#endif

#ifdef __VIC_WIN

//This function performs as getchar() in the c std.
//return -1 as error.
int __get_char_win()
{
    PINPUT_RECORD pBuffer = NULL;
    pBuffer = malloc(1024 * 64);
    if (pBuffer == NULL)
    {
        Sleep(1000);
        return -1;
    }
    DWORD nLength = (1024 * 64) / sizeof(INPUT_RECORD);
    DWORD nums;
    LPDWORD lpNumberOfEventsRead = &nums;
    if (!ReadConsoleInput(hConsole, pBuffer, nLength, lpNumberOfEventsRead))
    {
        return -1;
    }
    for (int i = 0; i < nums; i++)
    {
        switch (pBuffer[i].EventType)
        {
            case KEY_EVENT:
                if(pBuffer[i].Event.KeyEvent.bKeyDown)
                {
                    return pBuffer[i].Event.KeyEvent.uChar.AsciiChar;
                }
                break;

            case WINDOW_BUFFER_SIZE_EVENT:
                break;

            //I do not wanna handle mouse event now.
            case MOUSE_EVENT:
            //Event belows must be handled by OS.
            case FOCUS_EVENT:
            case MENU_EVENT:
            default:
                break;
        }
    }
    return -1;
}

#endif
