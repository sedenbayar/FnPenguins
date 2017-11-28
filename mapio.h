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
int read_data(char* ifilename, struct Gmdt *gmdt);

/////////
// Can //
/////////
int write_data(char* ofilename, struct Gmdt *gmdt);

#endif // MAPIO_H_INCLUDED
