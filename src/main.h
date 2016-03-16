//
// Created by yzy on 3/13/16.
//

#ifndef VIC_MAIN_H
#define VIC_MAIN_H

int main(int, char **);

int init_global();

#ifdef __linux__
#define __VIC_POSIX
#pragma message("OS: LINUX")
#endif

#ifdef __APPLE__
#define __VIC_POSIX
#pragma message("OS: OSX")
#endif

#ifdef _WIN32
#define __VIC_WIN
#pragma message("OS: WINDOWS")
#endif

#endif //VIC_MAIN_H
