//
//  display.c
//  board
//
//  Created by app on 2017/11/21.
//  Copyright © 2017年 ning. All rights reserved.
//

#include "display.h"
#include "env.h"

void print_map(char **data, int rows, int columns){
    printf("\n\n");
    int i,j;
    printf("    ");
    for(j=0;j<columns;j++){
        if(!(j/10))
            clrprintf(YELLOW,BLACK,"%d   ",j);// little difference ;)
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
            printf("%c   ",data[j][i]);
        }
        printf("\n\n");
    }
}
