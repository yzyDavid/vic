//
// Created by yzy on 3/13/16.
//

#ifndef VIC_MAIN_H
#define VIC_MAIN_H

int main(int, char **);

int init_global();

#ifdef __linux
#pragma message("OS: LINUX")
#endif

#ifdef _WIN32
#pragma message("OS: WINDOWS")
#endif

#endif //VIC_MAIN_H
