////
//  display.c
//  board
//
//  Created by app on 2017/11/21.
//  Copyright © 2017年 ning. All rights reserved.
//  with some changes Adam Domoslawski. 
//  All rights reserved 
//  

#include "display.h"
#include "env.h"


void print_map(char **data, int rows, int columns, int crnt_player){
    printf("\n\n");
    int i,j;
    printf("    ");
    for(j=0;j<columns;j++){
        if(!(j/10))
            clrprintf(YELLOW,BLACK,"%d   ",j);
        else
            clrprintf(YELLOW, BLACK,"%d  ",j);
    }
    printf("\n\n");
    for(i=0;i<rows;i++){
        if(!(i/10))
            clrprintf(YELLOW,BLACK,"%d  ", i);
        else
            clrprintf(YELLOW,BLACK,"%d ", i);
        if(!(i % 2))
            printf("  ");
        for(j=0;j<columns;j++){
            int plxr ;
            for ( plxr=1; plxr<=6; plxr++)
            {
                if(plxr==crnt_player)
                {
                    if((data[j][i]!=96+crnt_player)&&(data[j][i]!=84+crnt_player)&&
                       (data[j][i]!=64+crnt_player)&&(data[j][i]!='2')&&(data[j][i]!='1')&&(data[j][i]!='3'))
                   {

                        clrprintf(RED, BLACK,"%c   ",data[j][i]);
                       break;
                   }
                    else if ((data[j][i]==96+crnt_player)||(data[j][i]==84+crnt_player)||
                       (data[j][i]==64+crnt_player))
                       {
                      clrprintf(GREEN, BLACK,"%c   ",data[j][i]);
                      break;
                       }
                    else
                    {
                        printf("%c   ",data[j][i]);
                       break;

                    }
                }
                else
                {
                    continue;
                }

            }


        }
        printf("\n\n");
    }
}
