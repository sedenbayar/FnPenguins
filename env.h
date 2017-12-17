#ifndef ENV_H_INCLUDED
#define ENV_H_INCLUDED

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

#endif // ENV_H_INCLUDED
