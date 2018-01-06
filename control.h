#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <stdbool.h>
#include "datastrc.h"

int count_points(int x,int y,char **map,int scores[6]);
void a_turn(struct Gmdt *gmdt);  //single turn for all players, 1st player moves all of his pngns, then second one etc.

void upleft(int dist,struct Gmdt *gmdt,int pg);
void left(int dist,struct Gmdt *gmdt,int pg);
void downleft(int dist,struct Gmdt *gmdt,int pg);
void upright(int dist,struct Gmdt *gmdt,int pg);
void right(int dist,struct Gmdt *gmdt,int pg);
void downright(int dist,struct Gmdt *gmdt,int pg);
void move_penguin(struct Gmdt *gmdt,int pg);

#endif // CONTROL_H_INCLUDED
