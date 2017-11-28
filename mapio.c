////////////////////
// mapio.c        //
// by David & Can //
////////////////////
#include "mapio.h"

///////////
// David //
///////////
int is_pos_correct(char c){
    if (c == ' ') return 1;
    if (c >= '1' && c <= '3') return 1;
    if (c >= 'a' && c <= 'f') return 1;
    if (c >= 'A' && c <= 'A') return 1;
    if (c >= 'U' && c <= 'Z') return 1;
    return 0;
}

int read_data(char* ifilename, struct Gmdt *gmdt){
    char* content;
    int fsize;
    FILE* f = fopen(ifilename, "r");

    // Determine the file size
    fseek(f, 0L, SEEK_END);
    fsize = (int)ftell(f);
    rewind(f);

    // Read the file
    //content = (char*)malloc(fsize*sizeof(char));
    int i;

    // Populate the scores array with 0's
    for (i = 0; i < 6; i++)
        gmdt->scores[i] = 0;

    int c;
    int n; // the index of the line currently processed
    int l; // the amount of characters in the current line

    for(i = 0, n = 0, l = 0; (c = fgetc(f)) != EOF; i++, l++){
        // First line
        if(n == 0){
            // Read the current player index
            if(l == 0) {
                gmdt->crnt_player = c - 48;
                if(gmdt->crnt_player > 5) return 1;
            }
            else if((l >= 2) && !((l-2) % 3) && l < 19) gmdt->scores[(l-2)/3] += 10*(c - 48);
            else if((l >= 3) && !((l-3) % 3) && l < 19) gmdt->scores[(l-2)/3] += c - 48;
        }
        // Second line
        else if (n == 1){
            if(l == 0) {
                gmdt->max_players = c - 48;
                if(gmdt->max_players > 5) return 2;
            }
        }
        // Third line
        else if (n == 2){
            if(l == 0) gmdt->max_pngns = c - 48;
            else if (c != '\n') gmdt->max_pngns = gmdt->max_pngns * 10 + c - 48;
        }

        // Fourth line
        else if (n == 3){
            if(l == 0){
                if (c == 'p') gmdt->phase = 1;
                else if (c == 'm') gmdt->phase = 2;
                else return 3;
            }
        }

        // Fifth line and further
        else if (n >= 4){
            //if(!is_pos_correct(c)) return 4;
            // TODO - Loading the map data
        }

        if(c == '\n'){
            n++;
            l = -1;
        }
    }

    // Debug values
    for (i = 0; i < 6; i++)
        printf("%d ", gmdt->scores[i]);
    printf("\nplayer = %d\n", gmdt->crnt_player);
    printf("maxplayer = %d\n", gmdt->max_players);
    printf("maxpen = %d\n", gmdt->max_pngns);
    printf("phase = %d\n", gmdt->phase);


    // DEBUG - Print it out
    //printf("content = %s\n", content);

    fclose(f);

    return 0;
}
