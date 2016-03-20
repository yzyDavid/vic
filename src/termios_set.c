//
// Created by yzy on 3/12/16.
//This file defines functions and variables relative to platform, handling console behaviors.
//
#include "main.h"
#include "log_module.h"

#ifdef __VIC_POSIX

#include <termios.h>

#endif

#ifdef __VIC_WIN

#include <windows.h>
#include <wincon.h>

#endif

#include <stdio.h>

#ifdef __VIC_WIN

#include <afxres.h>
#include <conio.h>

#endif

#include "termios_set.h"
#include "draw_ui.h"

#ifdef __VIC_POSIX
static struct termios disabled;
static struct termios enabled;
#endif

#ifdef __VIC_WIN

//This might be useless.
static HANDLE hConsole = 0;

//according to msdn, this handle should the one we use to control the input.
HANDLE hStdIn = 0;
HANDLE hStdOut = 0;

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

//!!!This function should be called once on starting if its under Windows!!!
//This function set the global hConsole.
//Also set console title.
//Also set console mode.
int __get_self_window_win()
{
    if (hStdIn != 0)
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
    DWORD console_mode = 0;
    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStdIn, &console_mode);
    SetConsoleMode(hStdIn, console_mode | ENABLE_WINDOW_INPUT);
    return 0;
}

#endif

#ifdef __VIC_WIN

//This function performs as getchar() in the c std.
//return -1 as error.
int __get_char_win()
{
    return getch();
    return getchar();
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
    if (!ReadConsoleInput(hStdIn, pBuffer, nLength, lpNumberOfEventsRead))
    {
        return -1;
    }
    for (int i = 0; i < nums; i++)
    {
        char log[100];
        sprintf(log, "%lu\n", nums);
        print_log(log);

        switch (pBuffer[i].EventType)
        {
            case KEY_EVENT:
                if (pBuffer[i].Event.KeyEvent.bKeyDown)
                {
                    char unicode[100] = {};
                    char target[100] = {};
                    memcpy(unicode, &pBuffer[i].Event.KeyEvent.uChar.UnicodeChar, sizeof(WCHAR));
                    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR) unicode, 1, target, 100, 0, 0);
                    return target[0];
//                    return pBuffer[i].Event.KeyEvent.uChar.AsciiChar;
                }
                break;

                //Might have problem here.
            case WINDOW_BUFFER_SIZE_EVENT:
                console_columns = (unsigned int) pBuffer[i].Event.WindowBufferSizeEvent.dwSize.X;
                console_lines = (unsigned int) pBuffer[i].Event.WindowBufferSizeEvent.dwSize.Y;
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
