#include "datastrc.h"
#include <stdlib.h>

void allocate_memory(struct Gmdt *gmdt){
    gmdt->map = (char**)malloc(gmdt->columns*sizeof(char*));
    int i;
    for (i = 0; i < gmdt->columns; i++)
        gmdt->map[i] = (char*)malloc(gmdt->rows*sizeof(char));
}
