////////////////
// control.c  //
// by Jakub   //
////////////////

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "control.h"
#include "mapio.h"
#include "datastrc.h"


// !IMPORTANT I was not sure about pngns_pos[][][], i mean, thought it would be like max 6 players and max 2 penguins per player
// You can just use the pointer, the size is dynamic - just use ***pngns_pos # David

int count_points(int x,int y,char **map,int scores[6]);
bool is_move_possible(int x,int y,int max_pl, int max_pg,int ***pngns_pos,char **map,int rows,int cols); //checks if move is possible
void a_turn(int max_pl,int max_pg,int ***pngns_pos,char **map,int scores[6],int rows,int cols);  //single turn for all players, 1st player moves all of his pngns, then second one etc.
void move_penguin(int pl,int pg,int max_pl, int max_pg,int ***pngns_pos,char **map,int scores[6],int rows,int cols)//changing coordinates function
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

        if(is_move_possible(x,y,max_pl,max_pg,pngns_pos,map,rows,cols))//function checks if floe with such coordinates is available
            cant_i=0;
        else
        {
            printf("Sorry, this floe is unavailable :C\n");
            cant_i=1;
        }
    }
    int pts=count_points(a,b,map,scores);
    scores[pl]+=pts;
    map[a][b] = ' ';
    printf("Your penguin is successfully moving to (%d,%d).\n",x,y);
    pngns_pos[pl][pg][0]=x;
    pngns_pos[pl][pg][1]=y;
    if (map[x][y]=='1')
    {
        map[x][y]='a'+pl;
    }
    else if (map[x][y]=='2')
    {
        map[x][y]='A'+pl;
    }
    else if (map[x][y]=='3')
    {
        map[x][y]='U'+pl;
    }
}
bool is_move_possible(int x,int y,int max_pl, int max_pg,int ***pngns_pos,char **map,int rows,int cols)
{
    int i=0,j=0;
    if(x>=cols||y>=rows){return false;}
    if(map[x][y]==' '){return false;}
    for(i;i<max_pl;i++)
    {
        for(j;j<max_pg;j++)
        {
            if(pngns_pos[i][j][0]==x&&pngns_pos[i][j][1]==y) {return false; break;}
        }
    }
    return true;
}
void a_turn(int max_pl,int max_pg,int ***pngns_pos,char **map,int scores[6],int rows,int cols)
{
    int i=0,j=0,k=0;
    for(j;j<max_pg;j++)
    {
        for(i=0;i<max_pl;i++)
        {
            system("cls");
            printf("%Player %d's turn!\n",i);
            for(k=0;k<max_pl;k++)
            {
                printf("P%d: %d\t", k, scores[k]);
            }
            printf("\n");
            print_map(map,rows,cols);
            move_penguin(i,j,max_pl,max_pg,pngns_pos,map,scores,rows,cols);
        }
    }
}
int count_points(int x,int y,char **map,int scores[6])
{
    if (is_pos_correct(map[x][y])>0)
    {
        return 1 + (is_pos_correct(map[x][y])-1)/6;
    }
    return 0;
}

void placement(int max_pl,int max_pg,int ***pngns_pos,char **map,int rows,int cols)
{
    int x,y;
    int i=0,j=0;
    for(i=0;i<max_pl;i++)
    {
        for(j=0;j<max_pg;j++)
        {
            system("cls");
            print_map(map,rows,cols);
            printf("\nPlease, enter initial coordinates for player %d, penguin %d: ",i,j);
            scanf("%d",&x);
            scanf("%d",&y);
            pngns_pos[i][j][0]=x;
            pngns_pos[i][j][1]=y;
            map[x][y]='a'+i;
        }
    }
}
