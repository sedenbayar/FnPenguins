#include "ai.h"
#define TRY_LIMIT 300
#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

int count_pngns(struct Gmdt *gmdt, int player){
    FILE *f;
    f = fopen("moraz.txt", "w");
    int x, y, c = 0;
    int ipc;
    for (y = 0; y < gmdt->rows; y++)
        for (x = 0; x < gmdt->columns; x++){
            ipc = is_pos_correct(gmdt->map[x][y]);
            fprintf(f, "\nipc = %d, player = %d, ipc-player = %d, ipc-player mod 6 = %d", ipc, player, ipc-player, (ipc-player)%6);
            if ((ipc > 0) && (!player || !((ipc-player) % 6)))
                c++;
        }
    fclose(f);
    return c;
}

void pl_increment(struct Gmdt *gmdt){
    if (gmdt->crnt_player < 1 || gmdt->crnt_player == gmdt->max_players)
        gmdt->crnt_player = 1;
    else
        gmdt->crnt_player++;
}

void place_penguin_ai(struct Gmdt *gmdt){
    printf("[AI]\tBeginning placement step:\n");
    if(!(gmdt->crnt_player)){
        printf("[AI]\t    The input state was the initial state, setting crnt_player to 1.\n");
        gmdt->crnt_player = 1;
    } else {
        printf("[AI]\t    The current player is P%d.\n", gmdt->crnt_player);
    }

    // Change phase if required
    if(count_pngns(gmdt, 0) == gmdt->max_players*gmdt->max_pngns){
        printf("[AI]\t    All penguins have already been placed. Switching to movement phase.\n");
        gmdt->phase = 2;
        printf("[AI]\tPlacement step complete.\n\n");
        return;
    }

    // Place the penguin randomly
    int pg = count_pngns(gmdt, gmdt->crnt_player);
    int i, x, y, f = 0;
    printf("[AI]\t    Placing the penguin #%d randomly:\n", pg);
    for (i = 0; i < TRY_LIMIT; i++){
        printf("[AI]\t\tRolling the dice... ");
        x = random_number(0, gmdt->columns-1);
        y = random_number(0, gmdt->rows-1);
        if (place_pg(gmdt, pg, x, y)){
            printf("got it! (%d, %d) is correct!\n", x, y);
            f = 1;
            break;
        }
        printf("nope! (%d, %d) invalid!\n", x, y);
    }
    if(!f){
        printf("[AI]\t    This will take bloody forever! Taking the first valid location\ninstead:\n");
        for (y = 0; y < gmdt->rows; y++){
            for (x = 0; x < gmdt->columns; x++){
                printf("[AI]\t\tChecking the location... ");
                if (place_pg(gmdt, pg, x, y)){
                    printf("got it! (%d, %d) is correct!\n", x, y);
                    f = 1;
                    break;
                }
                printf("nope! (%d, %d) invalid!\n", x, y);
            }
            if (f) break;
        }
    }
    if(f){
        printf("[AI]\t    The penguin was deposited at (%d, %d).\n", x, y);
        pl_increment(gmdt);
        printf("[AI]\tRelinquishing control to P%d.\n", gmdt->crnt_player);
        printf("[AI]\tPlacement step complete.\n\n");
        return;
    } else {
        printf("[AI]\t    This map sucks, lmao. Ain't no suitable place to drop the penguin.\n", x, y);
        printf("[AI]\t    Timeout. The penguin was dropped into a volcano.\n", x, y);
        printf("[AI]\t    Placement step aborted. Go fix your bloody map first, newbs.\n\n", x, y);
        return;
    }
}

int estimate_mvmnt(struct Gmdt *gmdt, int pg, int dir){
    switch(dir){
    case 1:
        return min(estimate_mvmnt(gmdt, pg, 3), gmdt->pngns_pos[gmdt->crnt_player-1][pg][1]+1);
    case 2:
        return min(estimate_mvmnt(gmdt, pg, 4), gmdt->pngns_pos[gmdt->crnt_player-1][pg][1]+1);
    case 3:
        return gmdt->pngns_pos[gmdt->crnt_player-1][pg][0]+1;
    case 4:
        return gmdt->columns - gmdt->pngns_pos[gmdt->crnt_player-1][pg][0];
    case 5:
        return min(estimate_mvmnt(gmdt, pg, 3), gmdt->rows - gmdt->pngns_pos[gmdt->crnt_player-1][pg][1]);
    case 6:
        return min(estimate_mvmnt(gmdt, pg, 4), gmdt->rows - gmdt->pngns_pos[gmdt->crnt_player-1][pg][1]);
    }
    return 0;
}

void move_player_ai(struct Gmdt *gmdt){
    printf("[AI]\tBeginning movement step:\n");
    printf("[AI]\t    The current player is P%d.\n", gmdt->crnt_player);
    int i;
    int* iz_kill = (int*)malloc(gmdt->max_pngns*sizeof(int));
    char aifname[] = "aiX.pgdt";
    aifname[2] = gmdt->crnt_player + '0';
    for (i = 0; i < gmdt->max_pngns; i++)
        iz_kill[i] = 0; // populate array

    printf("[AI]\t    Selecting a random penguin... ");
    int pg = random_number(0, gmdt->max_pngns-1);

    while(1){ // Breaks upon successful movement
        printf("#%d selected!\n", pg);

        printf("[AI]\t    Formulating a random strategy:\n");

        int dir, dist, f = 0;
        int x, y;
        for (i = 0; i < TRY_LIMIT; i++){
            printf("[AI]\t\tRolling the dice...");
            dir = random_number(1, 6);
            dist = random_number(1, estimate_mvmnt(gmdt, pg, dir));
            //printf("[dir =%d, dist=%d]", dir, dist);
            f = move_penguin_ai(dist, gmdt, pg, gmdt->crnt_player-1, dir);
            if (f){
                printf("got it! Dir%d x %d is correct!\n", dir, dist);
                break;
            }
            printf("nope! Dir%d x %d is invalid!\n", dir, dist);
        }
        if(!f){
            printf("[AI]\t    This will take bloody forever! Taking the first valid move instead:\n");
            for (dist = 1, i = 0; i < gmdt->rows*gmdt->columns; dist++){
                for (dir = 1; dir <= 6; dir++, i++){
                    printf("[AI]\t\tChecking the move... ");
                    f = move_penguin_ai(dist, gmdt, pg, gmdt->crnt_player-1, dir);
                    if (f){
                        printf("got it! Dir%d x %d is correct!\n", dir, dist);
                        break;
                    }
                    printf("nope! Dir%d x %d is invalid!\n", dir, dist);
                }
                if (f) break;
            }
        }
        if (f){
            // Successful movement
            x = gmdt->pngns_pos[gmdt->crnt_player-1][pg][0];
            y = gmdt->pngns_pos[gmdt->crnt_player-1][pg][1];
            printf("[AI]\t    The penguin marched to (%d, %d).\n", x, y);

            printf("[AI]\t    Writing data to %s...\n", aifname);
            FILE* aif = fopen(aifname, "w");
            if (!aif){
                printf("[AI]\t    Error opening the '%s' file! It's not critical, but the\n", aifname);
                printf("game-over conditions won't be checked for automatically!\n");
            } else {
                fseek(aif, 0L, SEEK_SET);
                fprintf(aif, "%d", 0);
            }
            fclose(aif);
            break;
        }
        else{
            printf("[AI]\t    This penguin appears to be stuck.\n", x, y);
            iz_kill[pg] = true;
            printf("[AI]\t    We ain't got no time - choosing the first non-stuck penguin...\n", x, y);
            for (pg = -1, i = 0; i < gmdt->max_pngns; i++)
                if (!iz_kill[i]){
                    pg = i;
                    printf("\t");
                    break;
                }
            if (pg == -1){
                printf("[AI]\t    Dammit! All penguins are stuck! Movement impossible.\n");
                printf("[AI]\t    Checking for a possible game-over condition...\n");
                printf("[AI]\t    Reading the '%s' file...\n", aifname);
                FILE* aif = fopen(aifname, "r+");
                if (!aif){
                    printf("[AI]\t    Error opening the '%s' file! It's not critical, but the\n", aifname);
                    printf("game-over conditions won't be checked for automatically!\n");
                    fclose(aif);
                    break;
                } else {
                    int gmovr;
                    fscanf(aif,"%d",&gmovr);
                    aifname[0] = 's'; aifname[1] = 'v';
                    //printf("[AI]\t    gmovr == %d.\n", gmovr);
                    if (!gmovr){
                        printf("[AI]\t    No game-over condition has been met previously.\n");
                        printf("[AI]\t    Initializing a game-over check, it will be evaluated\n");
                        printf("again if the other players make no moves in the following round.\n");

                        fseek(aif, 0L, SEEK_SET);
                        fprintf(aif,"%d",1);
                        fclose(aif);

                        save_file(aifname, gmdt);
                    } else {
                        printf("[AI]\t    A game-over condition check found. Evaluating...\n");
                        save_file("temp.pgdt", gmdt);
                        if(compare_files(aifname, "temp.pgdt")){
                            printf("[AI]\t    No player has made a move since the last check.\n");
                            printf("[AI]\tMovement step complete.\n");
                            printf("[AI]\tThe game is over.\n");
                            printf("[AI]\tThe scores are as follows:\n");
                            int winc = 0, winscr = 0;
                            int winners[6] = {0};
                            for (i = 0; i < gmdt->max_players; i++){
                                printf("P%d: %d\n", i+1, gmdt->scores[i]);
                                winscr = max(winscr, gmdt->scores[i]);
                            }
                            for (i = 0; i < gmdt->max_players; i++){
                                if (gmdt->scores[i] == winscr){
                                    winners[winc] = i+1;
                                    winc++;
                                }
                            }
                            printf("\n\n");
                            if (winc == 1 && winners[0] == gmdt->crnt_player){
                                printf("[AI]\tAnd the winner is...\n\tPlayer %d. The one that was controlled by this unit.\n", winners[0]);
                                printf("[AI]\tgg ez, lol");
                            } else if (winc == 1){
                                printf("[AI]\tAnd the winner is...\nPlayer %d. Phew, not impressed. You got lucky.\n");
                            } else {
                                printf("[AI]\tAnd the winners are...");
                                bool boast = false;
                                for (i = 0; i < winc; i++){
                                    printf("Player %d%s", winners[i], ", ");
                                    if(winners[i] == gmdt->crnt_player)
                                        boast = true;
                                }
                                printf("tied for the highest place.\n");
                                if (boast)
                                    printf("Nice job tying this unit, next time processing power higher than\napprox. 13 Hz will be utilized, though, and all enemies shall be vanquished.\n");
                                else
                                    printf("A bunch of luckers and hax0rz. Not impressed.\n");
                            }
                            return;
                        }
                        else {
                            printf("[AI]\t    Moves have been made since the last check, the game continues.\n");
                            remove("temp.pgdt");
                        }
                    }
                    break;
                }
            }
        }
    }

    pl_increment(gmdt);
    printf("[AI]\tRelinquishing control to P%d.\n", gmdt->crnt_player);
    printf("[AI]\tMovement step complete.\n\n");
    free(iz_kill);
}
