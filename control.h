#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <stdbool.h>
#include "datastrc.h"

void placement(int max_pl,int max_pg,int ***pngns_pos,char **map,int rows,int cols);
int count_points(int x,int y,char **map,int scores[6]);
void move_penguin(int x,int y,int max_pl, int max_pg,int ***pngns_pos,char **map,int scores[6],int rows,int cols);
bool is_move_possible(int pl,int pg,int max_pl, int max_pg,int ***pngns_pos,char **map,int rows,int cols);
void a_turn(int max_pl,int max_pg,int ***pngns_pos,char **map,int scores[6],int rows,int cols);

#endif // CONTROL_H_INCLUDED
