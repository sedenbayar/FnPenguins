#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <stdbool.h>
#include "datastrc.h"
#include "mapio.h"
#include "env.h"

int count_points(int x,int y,struct Gmdt *gmdt);
void a_turn(struct Gmdt *gmdt);  //single turn for all players, 1st player moves all of his pngns, then second one etc.

bool upleft(int dist,struct Gmdt *gmdt,int pg,int pl);
bool left(int dist,struct Gmdt *gmdt,int pg,int pl);
bool downleft(int dist,struct Gmdt *gmdt,int pg,int pl);
bool upright(int dist,struct Gmdt *gmdt,int pg,int pl);
bool right(int dist,struct Gmdt *gmdt,int pg,int pl);
bool downright(int dist,struct Gmdt *gmdt,int pg,int pl);
void move_penguin(struct Gmdt *gmdt,int pg,int pl);
void placement(struct Gmdt *gmdt);
bool place_pg(struct Gmdt *gmdt,int j,int x,int y);
bool move_penguin_ai(int dist,struct Gmdt *gmdt,int pg,int pl,int way);

#endif // CONTROL_H_INCLUDED
