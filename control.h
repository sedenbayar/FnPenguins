#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <stdbool.h>

void move_penguin(int x,int y,int max_pl, int max_pg,int pngns_pos[6][2][2]);
bool is_move_possible(int pl,int pg,int max_pl, int max_pg,int pngns_pos[6][2][2]);
void a_turn(int max_pl,int max_pg,int pngns_pos[6][2][2]);

#endif // CONTROL_H_INCLUDED
