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
#include <set>
#include <map>
#include <vector>
#include "limit.h"
#include "MonteCarlo.h"

//baseLine means the greedy algorithm
class BaseLine
{
private:
    std::map<int,int> node_id_map;
    MonteCarlo *mc;
    
    //tmp variables;
    std::vector<int> seeds;
    std::vector<double> spreads;
    std::set<int> seedset;
public:
    BaseLine(Graph *graph);
    ~BaseLine();
    void run();
    int nextSeed();
    void greedyCELF();
    std::vector<int> getSeed();
    std::vector<double> getSpread();
};
#endif /* defined(__imms__BaseLine__) */
