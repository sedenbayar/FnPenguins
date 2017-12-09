//
//  mapgen.h
//  board
//
//  Created by app on 2017/11/28.
//  Copyright © 2017年 ning. All rights reserved.
//

#ifndef mapgen_h
#define mapgen_h

#include <stdio.h>
#include<time.h>
#include "datastrc.h"

int rand();
int random_number(int min, int max);
void generate_map(struct Gmdt *gmdt);

#endif /* mapgen_h */
