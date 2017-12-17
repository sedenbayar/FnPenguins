#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "env.h"

#define OS_WIN 1
#define OS_LINUX 2
#define OS_UNKNWN 3

#if defined(_WIN32) || defined(_WIN64)
    const int os = OS_WIN;
    #include <windows.h>

    int get_color_code(int text, int bg){
        return text+16*bg;
    }

    void set_colors(int text, int bg){
        HANDLE cnsl;
        cnsl = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(cnsl, get_color_code(text, bg));
    }

    void reset_colors(){
        set_colors(DEFAULT_TEXT, DEFAULT_BG);
    }
#else
#ifdef __linux
    const int os = OS_LINUX;

    void set_colors(int text, int bg){
        printf("\e[%dm\e[%dm", text, bg+10);
    }

    void reset_colors(){
        printf("\e[0m");
    }
#else
    const int os = OS_UNKNWN;

    void set_colors(int text, int bg){
    }

    void reset_colors(){
    }
#endif
#endif

const int COLORS[16] = { BLACK, GRAY, DARK_RED, DARK_YELLOW,
                DARK_GREEN, DARK_AQUA, DARK_BLUE, DARK_PINK,
                LIGHT_GRAY, RED, YELLOW, GREEN,
                AQUA, BLUE, PINK, WHITE };

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
        return 1;
    }
    else if (os == OS_LINUX){
        system("clear");
        return 1;
    } else {
        return 0;
    }
}
