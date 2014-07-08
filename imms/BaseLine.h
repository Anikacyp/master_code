//
//  BaseLine.h
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#ifndef __imms__BaseLine__
#define __imms__BaseLine__

#include <iostream>
#include "limit.h"
#include "MonteCarlo.h"

//baseLine means the greedy algorithm
class BaseLine
{
public:
    BaseLine();
    ~BaseLine();
    void run();
    int nextSeed();
};
#endif /* defined(__imms__BaseLine__) */
