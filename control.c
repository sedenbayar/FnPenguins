////////////////
// control.c  //
// by Jakub   //
////////////////

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "control.h"
#include "datastrc.h"


// !IMPORTANT I was not sure about pngns_pos[][][], i mean, thought it would be like max 6 players and max 2 penguins per player



bool is_move_possible(int x,int y,int max_pl, int max_pg,int pngns_pos[6][2][2]); //checks if move is possible
void a_turn(int max_pl,int max_pg,int pngns_pos[6][2][2]);  //single turn for all players. 1st player moves all of his pngns, then second one etc.
void move_penguin(int pl,int pg,int max_pl, int max_pg,int pngns_pos[6][2][2])//changing coordinates function
{

    int x,y;//new coordinates
    bool cant_i=1;//useful variable in determining floe availability, if equals "1" the availability must be checked
    //max_pl is for max_players
    //max_pg is for max_penguins
    //pl is for crnt_player index
    //pg is for crnt_player's penguin index shortcuts make it transparent
    int a=pngns_pos[pl][pg][0];
    int b=pngns_pos[pl][pg][1];
    printf("Your coordinates are (%d,%d). ",a,b);
    while(cant_i)
    {
        printf("Where would you like to move?");
        scanf("%d",&x);
        scanf("%d",&y);

        if(is_move_possible(x,y,max_pl,max_pg,pngns_pos[6][2][2]))//function checks if floe with such coordinates is available
            cant_i=0;
        else
        {
            printf("Sorry, this floe is unavailable :C\n");
            cant_i=1;
        }
    }
    printf("Your penguin is successfully moving to (%d,%d).",x,y);
    pngns_pos[pl][pg][0]=x;
    pngns_pos[pl][pg][1]=y;
}
bool is_move_possible(int x,int y,int max_pl, int max_pg,int pngns_pos[6][2][2])
{
    int i=0,j=0;
    for(i;i<max_pl;i++)
    {
        for(j;j<max_pg;j++)
        {
            if(pngns_pos[i][j][0]==x&&pngns_pos[i][j][1]==y) {return false; break;}
        }
    }
    return true;
}
void a_turn(int max_pl,int max_pg,int pngns_pos[6][2][2])
{
    int i=1,j=1;
    for(i;i<=max_pl;i++)
    {
        for(j;j<=max_pg;j++)
        {
            move_penguin(i,j,max_pl,max_pg,pngns_pos[6][2][2]);
        }
    }
}
