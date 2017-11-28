//
//  display.c
//  board
//
//  Created by app on 2017/11/21.
//  Copyright © 2017年 ning. All rights reserved.
//

#include "display.h"

void print_map(char **data, int rows, int columns){
    int i,j;
    for(i=0;i<rows;i++){
        if(!(i % 2))
            printf(" ");
        for(j=0;j<columns;j++){
            printf(" %c",data[j][i]);
        }
        printf("\n");
    }
}
