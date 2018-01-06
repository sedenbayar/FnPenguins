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

int count_points(int x,int y,char **map,int scores[6]);
void a_turn(struct Gmdt *gmdt);  //single turn for all players, 1st player moves all of his pngns, then second one etc.

void upleft(int dist,struct Gmdt *gmdt,int pg);
void left(int dist,struct Gmdt *gmdt,int pg);
void downleft(int dist,struct Gmdt *gmdt,int pg);
void upright(int dist,struct Gmdt *gmdt,int pg);
void right(int dist,struct Gmdt *gmdt,int pg);
void downright(int dist,struct Gmdt *gmdt,int pg);

void move_penguin(struct Gmdt *gmdt,int pg)//moving penguins function
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
        switch(way){
            case 1:  upleft(dist,&gmdt,pg);                           cant_i=0; break;
            case 2:  upright(dist,&gmdt,pg);                          cant_i=0; break;
            case 3:  left(dist,&gmdt,pg);                             cant_i=0; break;
            case 4:  right(dist,&gmdt,pg);                            cant_i=0; break;
            case 5:  downleft(dist,&gmdt,pg);                         cant_i=0; break;
            case 6:  downright(dist,&gmdt,pg);                        cant_i=0; break;
            default: printf("Sorry, %d is not valid direction.",way); cant_i=1; break;
        }

    }
    
    int pts=count_points(a,b,struct Gmdt *gmdt);
    gmdt->scores[gmdt->crnt_player]+=pts; 
    
    gmdt->map[a][b] = ' ';
    printf("Your penguin is successfully moving to (%d,%d).\n",x,y);
    pngns_pos[pl][pg][0]=x;
    pngns_pos[pl][pg][1]=y;
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
    int i=0,j=0,k=0;
    for(j;j<(gmdt->max_pngns);j++)
    {
        for(i=0;i<(gmdt->max_players);i++)
        {
            system("cls");
            printf("%Player %d's turn!\n",i);
            for(k=0;k<max_pl;k++)
            {
                printf("P%d: %d\t", k, scores[k]);
            }
            printf("\n");
            print_map(gmdt->map,gmdt->rows,gmdt->columns);
            move_penguin(&gmdt,j);
        }
    }
}
int count_points(int x,int y,&gmdt)
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
    for(i=0;i<max_pl;i++)
    {
        for(j=0;j<max_pg;j++)
        {
            system("cls");
            print_map(gmdt->map,gmdt->rows,gmdt->columns);
            printf("\nPlease, enter initial coordinates for player %d, penguin %d: ",i,j);
            scanf("%d",&x);
            scanf("%d",&y);
            gmdt->pngns_pos[i][j][0]=x;
            gmdt->pngns_pos[i][j][1]=y;
            gmdt->map[x][y]='a'+i;
        }
    }
}



//PENGUINS' MOVEMENT:
void upleft(int dist,struct Gmdt *gmdt,int pg)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    bool b
    {
        for(i;i<dist;i++)
        {
            for(k;k<(gmdt->max_players);k++)
            {
                for(j;j<(gmdt->max_pngns;j++)
                {
                    if(((gmdt->pngns_pos[k][j][0]==(x-i)&&gmdt->pngns_pos[k][j][1]==(y-i)))||gmdt->map[x-i][y-i]==' ') {gmdt->pngns_pos[pl][pg][0]=(x-i+1); gmdt->pngns_pos[pl][pg][1]=(y-i+1); printf("\nYour penguin encountered an obstacle.\n") return false; break;;}
                }
            }

        }
    }
    if(b)
    {
        gmdt->pngns_pos[pl][pg][0]=(x-i);
        gmdt->pngns_pos[pl][pg][1]=(y-i);
    }
}
void left(int dist,struct Gmdt *gmdt,int pg)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    bool b
    {
        for(i;i<dist;i++)
        {
            for(k;k<(gmdt->max_players);k++)
            {
                for(j;j<(gmdt->max_pngns;j++)
                {
                    if((gmdt->pngns_pos[k][j][0]==(x-i)&&gmdt->pngns[k][j][1]==y)||gmdt->map[x-i][y]==' ') {gmdt->pngns_pos[pl][pg][0]=(x-i+1); printf("\nYour penguin encountered an obstacle.\n") return false; break;;}
                }
            }

        }
    }
    if(b)
    {
        gmdt->pngns_pos[pl][pg][0]=(x-i);
    }
}
void downleft(int dist,struct Gmdt *gmdt,int pg)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    bool b
    {
        for(i;i<dist;i++)
        {
            for(k;k<(gmdt->max_players);k++)
            {
                for(j;j<(gmdt->max_pngns;j++)
                {
                    if(((gmdt->pngns_pos[k][j][0]==(x-i)&&gmdt->pngns_pos[k][j][1]==(y+i)))||gmdt->map[x-i][y+i]==' ') {gmdt->pngns_pos[pl][pg][0]=(x-i+1); gmdt->pngns_pos[pl][pg][1]=(y+i-1); b=0; printf("\nYour penguin encountered an obstacle.\n") return false; break;;}
                }
            }

        }
    }
    if(b)
    {
        gmdt->pngns_pos[pl][pg][0]=(x-i);
        gmdt->pngns_pos[pl][pg][1]=(y+i);
    }
}
void upright(int dist,struct Gmdt *gmdt,int pg)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    bool b
    {
        for(i;i<dist;i++)
        {
            for(k;k<(gmdt->max_players);k++)
            {
                for(j;j<(gmdt->max_pngns;j++)
                {
                    if(((gmdt->pngns_pos[k][j][0]==(x+i)&&gmdt->pngns_pos[k][j][1]==(y-i)))||gmdt->map[x+i][y-i]==' ') {gmdt->pngns_pos[pl][pg][0]=(x+i-1); gmdt->pngns_pos[pl][pg][1]=(y-i+1); printf("\nYour penguin encountered an obstacle.\n") return false; break;;}
                }
            }

        }
    }
    if(b)
    {
        gmdt->pngns_pos[pl][pg][0]=(x+i);
        gmdt->pngns_pos[pl][pg][1]=(y-i);
    }
}
void right(int dist,struct Gmdt *gmdt,int pg)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    bool b
    {
        for(i;i<dist;i++)
        {
            for(k;k<(gmdt->max_players);k++)
            {
                for(j;j<(gmdt->max_pngns;j++)
                {
                    if(((gmdt->pngns_pos[k][j][0]==(x+i)&&gmdt->pngns_pos[k][j][1]==(y)))||gmdt->map[x+i][y]==' ') {gmdt->pngns_pos[pl][pg][0]=(x+i-1); gmdt->pngns_pos[pl][pg][1]=(y); printf("\nYour penguin encountered an obstacle.\n") return false; break;;}
                }
            }

        }
    }
    if(b)
    {
        gmdt->pngns_pos[pl][pg][0]=(x+i);
    }
}
void downright(int dist,struct Gmdt *gmdt,int pg)
{
    int x=gmdt->pngns_pos[pl][pg][0];
    int y=gmdt->pngns_pos[pl][pg][1];
    int i=1,j=0,k=0;
    bool b
    {
        for(i;i<dist;i++)
        {
            for(k;k<(gmdt->max_players);k++)
            {
                for(j;j<(gmdt->max_pngns;j++)
                {
                    if(((gmdt->pngns_pos[k][j][0]==(x+i)&&gmdt->pngns_pos[k][j][1]==(y+i)))||map[x+i][y+i]==' ') {gmdt->pngns_pos[pl][pg][0]=(x+i-1); gmdt->pngns_pos[pl][pg][1]=(y+i-1); b=0; printf("\nYour penguin encountered an obstacle.\n") return false; break;;}
                }
            }

        }
    }
    if(b)
    {
        gmdt->pngns_pos[pl][pg][0]=(x+i);
        gmdt->pngns_pos[pl][pg][1]=(y+i);
    }
}
