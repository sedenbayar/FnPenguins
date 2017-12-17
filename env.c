#include <stdio.h>
#include <stdlib.h>
#include "env.h"

#define OS_WIN 1
#define OS_LINUX 2
#define OS_UNKNWN 3

#if defined(_WIN32) || defined(_WIN64)
    const int os = OS_WIN;
    #include <windows.h>
#else
#ifdef __linux
    const int os = OS_LINUX;
#else
    const int os = OS_UNKNWN;
#endif
#endif

int get_color_code(int text, int bg){
    if (os == OS_WIN){
        return text+16*bg;
    }
}

void set_colors(int text, int bg){
    if (os == OS_WIN){
        HANDLE cnsl;
        cnsl = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(cnsl, get_color_code(text, bg));
    }
}

void reset_colors(){
    if (os == OS_WIN){
        set_colors(DEFAULT_TEXT, DEFAULT_BG);
    }
}

int clrprintf(int text_clr, int bg_clr, const char *format, ...){
    set_colors(text_clr, bg_clr);

    va_list args;
    va_start(args, format);
    int rtrnval = vprintf(format, args);
    va_end(args);

    reset_colors();

    return rtrnval;
}

int clear(){
    if (os == OS_WIN){
        system("cls");
    }
}
