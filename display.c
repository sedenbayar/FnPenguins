//
//  display.c
//  board
//
//  Created by app on 2017/11/21.
//  Copyright © 2017年 ning. All rights reserved.
//

#include "display.h"

void print_map(char data[100][100], int rows, int columns){
    int i,j;
    for(i=0;i<columns;i++){
        if(!(i % 2))
            printf(" ");
        for(j=0;j<rows;j++){
            printf(" %c",data[i][j]);
        }
        printf("\n");
    }
}
