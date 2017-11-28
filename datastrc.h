////////////////
// datastrc.h //
// by David   //
////////////////
#ifndef DATASTRC_H_INCLUDED
#define DATASTRC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/* Instead of passing all the variables to each function, we can just
   wrap them together in a struct and pass the whole struct.
   To create a struct, define it like this:
   struct Gmdt whatever;
   Replacing "whatever" with a name. I recommend calling it "gmdt"
   (all lowercase) everywhere, just for the sake of convenience.
   
   To access a variable from this struct, for example "rows", say:
   whatever.rows
   For example:
   printf("%d", whatever.rows);
   
   To create a function that takes a struct as an argument, just take
   a pointer to it:
   void some_function(struct Gmdt *whatever){
       //function code goes here
   }.
   
   Similarly, to pass a struct into such function so that it can alter
   the struct directly, use the "&" operator, just like in scanf:
   some_function(&whatever);
   
   However, when having just a pointer to the struct, one needs to
   get the values using the -> operator instead. For example:
   whatever->rows
   Instead of whatever.rows.                                         */
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
    
    int phase; // The current phase (1 for placement, 2 for movement)
    
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
