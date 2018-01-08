#include <stdio.h>
#include "display.h"
#include "mapio.h"
#include "datastrc.h"
#include "control.h"

int main(int argc, char *argv){


if(argc == 2)
   {
    read_data(argv[1], *gmdt);

    place_penguin_ai(&gmdt);
    move_player_ai(&gmdt);

   }
   else {
    printf("Insufficient arguments.\nUsage: program.exe inputFileName outputFileName");
    return 1;
   }

}

if(gmdt->phase == 1){
    place_penguin(*gmdt);

    //update phase

    save_file(argv[2], *gmdt);
    free_memory(struct Gmdt, *gmdt);
    free_pngns(struct Gmdt, *gmdt);
    return 0;
}

if(gmdt->phase == 2){
    move_player(*gmdt);
    //move_player functions update current player number


    save_file(argv[2], *gmdt);
    free_memory(struct Gmdt, *gmdt);
    free_pngns(struct Gmdt, *gmdt);
    return 0;
}
