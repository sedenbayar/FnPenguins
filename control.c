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

#define Y_FIX 0

int count_points(int x,int y,struct Gmdt *gmdt);
void a_turn(struct Gmdt *gmdt);  //single turn for all players, 1st player moves all of his pngns, then second one etc.

bool upleft(int dist,struct Gmdt *gmdt,int pg,int pl);
bool left(int dist,struct Gmdt *gmdt,int pg,int pl);
bool downleft(int dist,struct Gmdt *gmdt,int pg,int pl);
bool upright(int dist,struct Gmdt *gmdt,int pg,int pl);
bool right(int dist,struct Gmdt *gmdt,int pg,int pl);
bool downright(int dist,struct Gmdt *gmdt,int pg,int pl);

void move_penguin(struct Gmdt *gmdt,int pg,int pl)//moving penguins function
{
    int way,dist;//way is direction of movement and dist is distance (number of floes)
    bool cant_i=1;//useful variable in determining movement availability, if equals "1" the availability must be checked
    //max_pl is for max_players
    //max_pg is for max_penguins
    //pl is for crnt_player index
    //pg is for crnt_player's penguin index, shortcuts make it transparent
    int a=gmdt->pngns_pos[pl][pg][0];
    int b=gmdt->pngns_pos[pl][pg][1];


    printf("Your coordinates are (%d,%d). ",a,b);
    while(cant_i)
    {
        printf("In which direction and how far would you like to go?\n 1: up-left    2: up-right\n 3: left       4: right\n 5: down-left  6: down-right\n");
        printf("Direction: ");
        scanf("%d",&way);
        printf("Distance: ");
        scanf("%d",&dist);
        if(dist == 0)
            return;
        else if (dist > 0){
            switch(way){
                case 1:  cant_i=!upleft(dist,gmdt,pg,pl); break;
                case 2:  cant_i=!upright(dist,gmdt,pg,pl); break;
                case 3:  cant_i=!left(dist,gmdt,pg,pl); break;
                case 4:  cant_i=!right(dist,gmdt,pg,pl); break;
                case 5:  cant_i=!downleft(dist,gmdt,pg,pl); break;
                case 6:  cant_i=!downright(dist,gmdt,pg,pl); break;
                default: printf("Sorry, %d is not valid direction.",way);    cant_i=1; break;
            }
        }
        printf("\nMovement invalid! Your penguin might have encountered an obstacle or you've given invalid data.\n");
    }

    int pts=count_points(a,b,gmdt);
    gmdt->scores[pl]+=pts;

    gmdt->map[a][b] = ' ';
    int x = gmdt->pngns_pos[pl][pg][0];
    int y = gmdt->pngns_pos[pl][pg][1];
    printf("Your penguin is successfully moving to (%d,%d).\n",x,y);
    if (gmdt->map[x][y]=='1')
    {
        gmdt->map[x][y]='a'+pl;
    }
    else if (gmdt->map[x][y]=='2')
    {
        gmdt->map[x][y]='A'+pl;
    }
    else if (gmdt->map[x][y]=='3')
    {
        gmdt->map[x][y]='U'+pl;
    }
}
void a_turn(struct Gmdt *gmdt)
{
    int j=0,k=0;
    for(j;j<(gmdt->max_pngns);j++)
    {
        for(gmdt->crnt_player = 1;gmdt->crnt_player<=(gmdt->max_players);gmdt->crnt_player++)
        {
            system("cls");
            printf("%Player %d's turn!\n",gmdt->crnt_player);
            for(k=0;k<gmdt->max_players;k++)
            {
                printf("P%d: %d\t", k+1, gmdt->scores[k]);
            }
            printf("\n");
            print_map(gmdt->map,gmdt->rows,gmdt->columns);
            move_penguin(gmdt,j,gmdt->crnt_player-1);
        }
    }
}
int count_points(int x,int y,struct Gmdt *gmdt)
{
    if (is_pos_correct(gmdt->map[x][y])>0)
    {
        return 1 + (is_pos_correct(gmdt->map[x][y])-1)/6;
    }
    return 0;
}

void placement(struct Gmdt *gmdt)
{
    int x,y;
    int i=0,j=0;
    bool is_correct = false;
    for(j=0;j<gmdt->max_pngns;j++)
    {
        for(gmdt->crnt_player=1; gmdt->crnt_player <= gmdt->max_players; gmdt->crnt_player++)
        {
            is_correct = false;
            system("cls");
            print_map(gmdt->map,gmdt->rows,gmdt->columns);
            while(!is_correct)
            {
                printf("\nPlease, enter initial coordinates for player %d, penguin %d: ",gmdt->crnt_player,j);
                scanf("%d",&x);
                scanf("%d",&y);
                if(gmdt->map[x][y] == '1')
                    is_correct = true;
                else
                    printf("\nThe target floe must contain exactly 1 fish!");
            }
            gmdt->pngns_pos[gmdt->crnt_player-1][j][0]=x;
            gmdt->pngns_pos[gmdt->crnt_player-1][j][1]=y;
            gmdt->map[x][y]='a'+gmdt->crnt_player-1;
        }
    }
}



//PENGUINS' MOVEMENT:
int xhex(int y,int d)
{
    if(d>=0)
        return d/2 + !((y + Y_FIX) % 2);
    else
        return d/2 - ((y + Y_FIX) % 2);
}
bool upleft(int dist,struct Gmdt *gmdt,int pg,int pl)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    for(i=1;i<=dist;i++)
    {
        if (gmdt->map[x+(xhex(y,-i))][y-i]==' ')
            return false;
        for(k=0;k<(gmdt->max_players);k++)
        {
            for(j=0;j<(gmdt->max_pngns);j++)
            {
                if((gmdt->pngns_pos[k][j][0]==(x+(xhex(y,-i)))&&gmdt->pngns_pos[k][j][1]==(y-i)))
                    return false;
            }
        }
    }
    if (i > dist) i = dist;
    gmdt->pngns_pos[pl][pg][0]=(x+xhex(y,-i));
    gmdt->pngns_pos[pl][pg][1]=(y-i);
    return true;
}
bool left(int dist,struct Gmdt *gmdt,int pg,int pl)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    for(i=1;i<=dist;i++)
    {
        if (gmdt->map[x-i][y]==' ')
            return false;
        for(k=0;k<(gmdt->max_players);k++)
        {
            for(j=0;j<(gmdt->max_pngns);j++)
            {
                if((gmdt->pngns_pos[k][j][0]==(x-i)&&gmdt->pngns_pos[k][j][1]==(y)))
                    return false;
            }
        }
    }
    if (i > dist) i = dist;
    gmdt->pngns_pos[pl][pg][0]=(x-i);
    return true;
}
bool downleft(int dist,struct Gmdt *gmdt,int pg,int pl)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    for(i=1;i<=dist;i++)
    {
        if (gmdt->map[x+(xhex(y,-i))][y+i]==' ')
            return false;
        for(k=0;k<(gmdt->max_players);k++)
        {
            for(j=0;j<(gmdt->max_pngns);j++)
            {
                if((gmdt->pngns_pos[k][j][0]==(x+(xhex(y,-i)))&&gmdt->pngns_pos[k][j][1]==(y+i)))
                    return false;
            }
        }
    }
    if (i > dist) i = dist;
    gmdt->pngns_pos[pl][pg][0]=(x+xhex(y,-i));
    gmdt->pngns_pos[pl][pg][1]=(y+i);
    return true;
}
bool upright(int dist,struct Gmdt *gmdt,int pg,int pl)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    for(i=1;i<=dist;i++)
    {
        if (gmdt->map[x+(xhex(y,i))][y-i]==' ')
            return false;
        for(k=0;k<(gmdt->max_players);k++)
        {
            for(j=0;j<(gmdt->max_pngns);j++)
            {
                if((gmdt->pngns_pos[k][j][0]==(x+(xhex(y,i)))&&gmdt->pngns_pos[k][j][1]==(y-i)))
                    return false;
            }
        }
    }
    if (i > dist) i = dist;
    gmdt->pngns_pos[pl][pg][0]=(x+xhex(y,i));
    gmdt->pngns_pos[pl][pg][1]=(y-i);
    return true;
}
bool right(int dist,struct Gmdt *gmdt,int pg,int pl)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    for(i=1;i<=dist;i++)
    {
        if (gmdt->map[x+i][y]==' ')
            return false;
        for(k=0;k<(gmdt->max_players);k++)
        {
            for(j=0;j<(gmdt->max_pngns);j++)
            {
                if((gmdt->pngns_pos[k][j][0]==(x+i)&&gmdt->pngns_pos[k][j][1]==(y)))
                    return false;
            }
        }
    }
    if (i > dist) i = dist;
    gmdt->pngns_pos[pl][pg][0]=(x+i);
    return true;
}

bool downright(int dist,struct Gmdt *gmdt,int pg,int pl)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    for(i=1;i<=dist;i++)
    {
        if (gmdt->map[x+(xhex(y,i))][y+i]==' ')
            return false;
        for(k=0;k<(gmdt->max_players);k++)
        {
            for(j=0;j<(gmdt->max_pngns);j++)
            {
                if((gmdt->pngns_pos[k][j][0]==(x+(xhex(y,i)))&&gmdt->pngns_pos[k][j][1]==(y+i)))
                    return false;
            }
        }
    }
    if (i > dist) i = dist;
    gmdt->pngns_pos[pl][pg][0]=(x+xhex(y,i));
    gmdt->pngns_pos[pl][pg][1]=(y+i);
    return true;
}
