//
//  BaseLine.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "BaseLine.h"

BaseLine::BaseLine(Graph *graph){
	mc=new MonteCarlo(graph);
    this->node_id_map=graph->getNodeIdMap();
}

BaseLine::~BaseLine(){
    delete mc;
}

void BaseLine::run()
{
    for(int i=0; i<SEED_SIZE; i++) {
        int seed=nextSeed();
        std::cout<<"seed "<<i+1<<" is "<<seed<<std::endl;
        seeds.push_back(seed);
        seedset.insert(seed);
    }
    std::cout<<seeds.size()<<std::endl;
}

int BaseLine::nextSeed()
{
    double value=0.0;
    int nexe_seed_id=-1;
    std::vector<int> tmp_seeds=seeds;
    std::map<int,int>::iterator iter=node_id_map.begin();
    while (iter!=node_id_map.end()) {
        if (!seedset.count(iter->first)) {
            tmp_seeds.push_back(iter->first);
            double spreadvalue=mc->simulation(NUM_ITER,tmp_seeds);
            if (value<spreadvalue) {
                value=spreadvalue;
                nexe_seed_id=iter->first;
            }
            tmp_seeds.pop_back();
        }
        iter++;
    }
    return nexe_seed_id;
}


void BaseLine::greedyCELF()
{
    
}