//
//  BaseLine.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "BaseLine.h"

BaseLine::BaseLine(){}
BaseLine::~BaseLine(){}

void BaseLine::run()
{
    double value = 0.0;
    std::vector<double> improve;
    std::vector<int> seeds;
    std::set<int> seedset;
    for (int i=0; i<SEED_SIZE; i++) {
        int seed=nextSeed();
    }
    
}

int BaseLine::nextSeed()
{
    
    return 1;
}