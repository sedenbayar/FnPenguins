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
   encountering specific errors.                      */
int read_data(char* ifilename, struct Gmdt *gmdt);

/////////
// Can //
/////////
int write_data(char* ofilename, struct Gmdt *gmdt);

#endif // MAPIO_H_INCLUDED
