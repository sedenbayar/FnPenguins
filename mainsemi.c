#include <stdio.h>
#include "display.h"
#include "mapio.h"
#include "datastrc.h"
#include "control.h"

int main(int argc, char &argv){

allocate_memory(*gmdt);
//First allocate some memory

allocate_pngns(*gmdt);
//allocate memory for penguins

read_data(argv[1], *gmdt);

if(gmdt->crnt_player == 0){
    generate_map(*gmdt);
    crnt_player = 2;
    write_data(*gmdt);
    return 1;
}

if(gmdt->phase == 1){
    place_penguin(*gmdt);

    //update phase

    write_data(*gmdt);
    return 1;
}

if(gmdt->phase == 2){
    get_movement(*gmdt)

    //we should discuss how to pass movement info to function

    move_player(*gmdt);

    //move_player functions update current player number

    write_data(*gmdt)
    return 1;

}
