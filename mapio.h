////////////////////
// mapio.h        //
// by David & Can //
////////////////////
#ifndef MAPIO_H_INCLUDED
#define MAPIO_H_INCLUDED

#include "datastrc.h"

///////////
// David //
///////////

// Checks if a character is correct with respect to the structure
int is_pos_correct(char c);

/* The return value from this function will represent
   the success (if there were any errors, etc.).
   It will return 0 on success, and other values when
   encountering specific errors regarding the file:
   1 - current player index is larger than 5
   2 - the max amount of players is greater than 6
   3 - the max amount of player is smaller than 2
   4 - unknown phase name given                      */
int read_data(char* ifilename, struct Gmdt *gmdt);

/////////
// Can //
/////////
void save_file(char* ofilename, struct Gmdt *gmdt);

#endif // MAPIO_H_INCLUDED
