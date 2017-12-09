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
    FILE* f = fopen(ifilename, "r");

    int i; // Counter for the for loops

    // Populate the scores array with 0's
    for (i = 0; i < 6; i++)
        gmdt->scores[i] = 0;

    // Read the file
    char c; // the last read character
    int n; // the index of the line currently processed
    int l; // the index of the current character with respect to the current line
    int lmax; // the biggest found amount of characters in a single map line
    long pos; // the stored position, in order to read the map-part once again after measuring the size

    for(i = 0, n = 0, l = 0, lmax = 0; (c = fgetc(f)) != EOF; i++, l++){
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

        // Fifth line and further - measure the size
        else if (n >= 4){
            if (n == 4 && l == 0) pos = ftell(f); // Store the position
            lmax = (l > lmax) ? l : lmax; // Keep lmax up to date
        }

        if(c == '\n'){
            n++;
            l = -1;
        }
    }

    gmdt->rows = n - 3;
    gmdt->columns = gmdt->rows == 1 ? lmax + 1 : lmax;

    // Allocate memory for the map array
    allocate_memory(gmdt);

    // Come back to the saved position
    fseek(f, pos-1, SEEK_SET);
    for(i = 0, n = 0, l = 0; (c = fgetc(f)) != EOF; i++, l++){
        // Read map characters
        if(c == '\n'){
            //printf("New line break.\n");
            n++;
            l = -1;
            continue;
        }
        //printf("Reading map[%d][%d]: %c\n", l, n, c);
        gmdt->map[l][n] = c;
    }

    fclose(f);

    return 0;
}
