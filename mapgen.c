/////////////////
// mapgen.c    //
// by Gao Ning //
/////////////////
#include "mapgen.h"
#include "datastrc.h"



int random_number(int min, int max){

    return (rand()%(max-min+1)+min);

}

void generate_map(struct Gmdt *gmdt){
    int i,j;
    int SIZE;
    srand((unsigned int)time(NULL));
    SIZE=random_number(16,22);
    gmdt->rows=SIZE;
    gmdt->columns=SIZE;

    allocate_memory(gmdt);

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
           gmdt->map[i][j]=random_number('0','3');
            if(gmdt->map[i][j]=='0')
            gmdt->map[i][j]=' ';

        }


    }



}
