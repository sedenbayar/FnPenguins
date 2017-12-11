////////////////
// datastrc.c //
// by David   //
////////////////
#include "datastrc.h"
#include <stdlib.h>

void allocate_memory(struct Gmdt *gmdt){
    gmdt->map = (char**)malloc(gmdt->columns*sizeof(char*));
    int i;
    for (i = 0; i < gmdt->columns; i++)
        gmdt->map[i] = (char*)malloc(gmdt->rows*sizeof(char));
}

void allocate_pngns(struct Gmdt *gmdt){
    int i, j;
    gmdt->pngns_pos = (int***)malloc(gmdt->max_players*sizeof(int**));
    for (i = 0; i < gmdt->max_players; i++)
        gmdt->pngns_pos[i] = (int**)malloc(gmdt->max_pngns*sizeof(int*));
    for (i = 0; i < gmdt->max_players; i++)
        for (j = 0; j < gmdt->max_pngns; j++)
            gmdt->pngns_pos[i][j] = (int*)malloc(2*sizeof(int));
}

void free_memory(struct Gmdt *gmdt){
    int i;
    for (i = 0; i < gmdt->columns; i++)
        free(gmdt->map[i]);
    free(gmdt->map);
}

void free_pngns(struct Gmdt *gmdt){
    int i, j;
    for (i = 0; i < gmdt->max_players; i++)
        for (j = 0; j < gmdt->max_pngns; j++)
            free(gmdt->pngns_pos[i][j]);
    for (i = 0; i < gmdt->max_players; i++)
        free(gmdt->pngns_pos[i]);
    free(gmdt->pngns_pos);
}
