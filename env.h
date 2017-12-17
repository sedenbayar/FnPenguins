#ifndef ENV_H_INCLUDED
#define ENV_H_INCLUDED

#if defined(_WIN32) || defined(_WIN64)
    #define BLACK 0
    #define DARK_BLUE 1
    #define DARK_GREEN 2
    #define DARK_AQUA 3
    #define DARK_RED 4
    #define DARK_PINK 5
    #define DARK_YELLOW 6
    #define LIGHT_GRAY 7
    #define GRAY 8
    #define BLUE 9
    #define GREEN 10
    #define AQUA 11
    #define RED 12
    #define PINK 13
    #define YELLOW 14
    #define WHITE 15

    #define DEFAULT_BG 0
    #define DEFAULT_TEXT 7

    int get_color_code(int text, int bg);
    void set_colors(int text, int bg);
    void reset_colors();
#else
#ifdef __linux
    #define BLACK 30
    #define DARK_BLUE 34
    #define DARK_GREEN 32
    #define DARK_AQUA 36
    #define DARK_RED 31
    #define DARK_PINK 35
    #define DARK_YELLOW 33
    #define LIGHT_GRAY 37
    #define GRAY 90
    #define BLUE 94
    #define GREEN 92
    #define AQUA 96
    #define RED 91
    #define PINK 95
    #define YELLOW 93
    #define WHITE 97

    #define DEFAULT_BG 30
    #define DEFAULT_TEXT 97

    void set_colors(int text, int bg);
    void reset_colors();
#else
    #define BLACK 30
    #define DARK_BLUE 34
    #define DARK_GREEN 32
    #define DARK_AQUA 36
    #define DARK_RED 31
    #define DARK_PINK 35
    #define DARK_YELLOW 33
    #define LIGHT_GRAY 37
    #define GRAY 90
    #define BLUE 94
    #define GREEN 92
    #define AQUA 96
    #define RED 91
    #define PINK 95
    #define YELLOW 93
    #define WHITE 97

    #define DEFAULT_BG 30
    #define DEFAULT_TEXT 97

    void set_colors(int text, int bg);
    void reset_colors();
#endif
#endif

const int COLORS[16];

int clrprintf(int text_clr, int bg_clr, const char *format, ...);
int clear();

#endif // ENV_H_INCLUDED
