#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "control.h"
#include "datastrc.h"
#include "mapio.h"
#include "mapgen.h"
#include <stdlib.h>
#include <stdbool.h>

void place_penguin_ai(struct Gmdt *gmdt);
void move_player_ai(struct Gmdt *gmdt);

#endif // AI_H_INCLUDED
