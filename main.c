#include <stdio.h>
#include <stdlib.h>
#include "datastrc.h"
#include "mapgen.h"
#include "mapio.h"
#include "control.h"
#include "display.h"
#include <time.h>

void init_settings(struct Gmdt *gmdt){
    do{
        printf("Number of players (2-6): ");
        scanf("%d", &gmdt->max_players);
    }while(gmdt->max_players < 2 || gmdt->max_players > 6);

    do{
        printf("Number of penguins per player (1 or greater): ");
        scanf("%d", &gmdt->max_pngns);
    }while(gmdt->max_pngns < 1);

    gmdt->phase = 1; // start with placement
    gmdt->crnt_player = 0; // start from the first player

    // Populate score array with 0's
    int i;
    for (i = 0; i < 6; i++)
        gmdt->scores[i] = 0;
}

int main(int argc, char* argv)
{
    struct Gmdt gmdt;
    srand((unsigned int)time(NULL));

    generate_map(&gmdt);

    // Initialize settings
    init_settings(&gmdt);

    // Allocate memory for the penguins
    allocate_pngns(&gmdt);

    //read_data("gie.txt", &gmdt);
    //print_map(gmdt.map, gmdt.rows, gmdt.columns);

    /*int i, j, k;
    for (i = 0; i < gmdt.max_players; i++)
        for (j = 0; j < gmdt.max_pngns; j++)
            printf("(%d, %d)\n", gmdt.pngns_pos[i][j][0], gmdt.pngns_pos[i][j][1]);*/

    // Player input here
    placement(gmdt.max_players, gmdt.max_pngns, gmdt.pngns_pos, gmdt.map, gmdt.rows, gmdt.columns);
    gmdt.phase = 2;
    system("cls");
    while(1)
    {
        a_turn(gmdt.max_players, gmdt.max_pngns, gmdt.pngns_pos, gmdt.map, gmdt.scores, gmdt.rows, gmdt.columns);
    }

    // Free memory
    free_memory(&gmdt);
    free_pngns(&gmdt);

    return 0;
}

