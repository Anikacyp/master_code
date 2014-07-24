//
//  BaseLine.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "BaseLine.h"

BaseLine::BaseLine(Graph *graph){
    this->node_id_map=graph->getNodeIdMap();
    mc=new MonteCarlo(graph);
}

BaseLine::~BaseLine(){
    delete mc;
}

void BaseLine::run()
{
    for(int i=0; i<SEED_SIZE; i++) {
        int seed=nextSeed();
        if (seed==-1) {
            return;
        }else
        {
        	seeds.push_back(seed);
        	seedset.insert(seed);
        }
    }
}

int BaseLine::nextSeed()
{
    double value=0.0;
    int nexe_seed_id=-1;
    std::vector<int> tmp_seeds=seeds;
    //std::cout<<"original seed size: "<<seeds.size()<<std::endl;
    std::map<int,int>::iterator iter=node_id_map.begin();
    while (iter!=node_id_map.end()) {
        if (!seedset.count(iter->first)) {
            tmp_seeds.push_back(iter->first);
            double spreadvalue=mc->simulation(NUM_ITER,tmp_seeds);
             //std::cout<<tmp_seeds.size()<<"\t"<<iter->first<<"\t"<<spreadvalue<<"\t"<<value<<std::endl;
            if (value<spreadvalue) {
                value=spreadvalue;
                nexe_seed_id=iter->first;
            }
            tmp_seeds.clear();
            tmp_seeds=seeds;
        }
        iter++;
    }
    //seed_spread[nexe_seed_id]=value;
    spreads.push_back(value);
    return nexe_seed_id;
}

//improved greedy algorithm
void BaseLine::greedyCELF()
{
    
}

std::vector<int> BaseLine::getSeed()
{
 	return seeds;
}
std::vector<double> BaseLine::getSpread()
{
    return spreads;
}