////////////////
// datastrc.h //
// by David   //
////////////////
#ifndef DATASTRC_H_INCLUDED
#define DATASTRC_H_INCLUDED

/* Instead of passing all the variables to each function, we can just
   wrap them together in a struct and pass the whole struct.          */
struct Gmdt {
    char **map;
    /* **map is a 2d array (pointer to a pointer) that stores the
       value of each point on the map as characters, accordingly
       to the data file structure.
       To get a value of a specific point, use map[x][y], x and y
       obviously being the coordinates. x is the column and y is
       the row here.
       The memory for this array should be allocated dynamically
       with the malloc() function, and with respect to the other
       variables in this struct, namely "rows" and "columns".    */
       
    int rows;
    int columns;
    /* These two variables determine the size of the map array, as
       mentioned above.                                            */
    
    int crnt_player; // Which player is making the next turn
    int max_players; // The total number of players for the current match
    int max_pngns; // The max/starting amount of penguins per player
    int scores[6]; // The score for every player
    
    int ***pngns_pos;
    /* This is a 3d array (a triple pointer) that stores the position
       of each penguin. 
       To get a single coordinate, use this:
       pngns_pos[p][r][n], where:
       p - the index of the player,
       r - the index of the penguin,
       n - which coordinate (0 for x, 1 for y).
       Similarly, to get an array of size 2, containing both coordinates:
       pngns_pos[p][r].
       The size of each dimension of this array should be with respect to
       the other variables from this struct, namely:
       pngns_pos[max_players][max_pngns][2].                              */
};

#endif // DATASTRC_H_INCLUDED
