#include <stdio.h>
#include "mapio.h"
#include "datastrc.h"
#include "control.h"
#include "ai.h"
#include "time.h"

int main(int argc, char *argv[]){

srand(time(NULL));
if(argc >= 3)
{
    struct Gmdt gmdt;
    read_data(argv[1], &gmdt);

    if(gmdt.phase == 1)
    {
        place_penguin_ai(&gmdt);
        // update phase
    }

    if(gmdt.phase == 2)
    {
        move_player_ai(&gmdt);
        //move_player functions update current player number
    }

    save_file(argv[2], &gmdt);
    free_memory(&gmdt);
    free_pngns(&gmdt);
    return 0;
}
    else {
     printf("Insufficient arguments.\nUsage: program.exe inputFileName outputFileName");
     return 1;
    }
}
