/* DON'T COMPILE THIS, THIS IS JUST A GENERAL CONCEPTION */

#include <stdio.h>
// other necessary includes
#include "display.h"
#include "mapio.h"
#include "control.h"
#include "datastrc.h"

int main(int argc, char **argv){

  // File: mapio.c
  // A function that will fill the variables according to the data
  // found in the input file.
  read_data(argv[1], map, &crnt_player, &max_players, etc...);

  // File: control.c
  // Wait for the player input, inform the player if the input was incorrect, etc.,
  // then alter the variables accordingly.
  // The print_map() function from the display.c file would be called inside of
  // the player_input function:
  // print_map(map, rows, columns)
  player_input(map, rows, columns, &crnt_player, etc...);

  // File: mapio.c
  // Output the variables into a file
  write_data(argv[2], map, rows, columns, crnt_player, etc...);
}
