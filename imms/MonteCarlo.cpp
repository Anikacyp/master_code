//
//  MonteCarlo.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "MonteCarlo.h"
MonteCarlo::MonteCarlo(){}

MonteCarlo::MonteCarlo(Graph *graph)
{
    setVariables(graph);
}
MonteCarlo::~MonteCarlo(){}

void MonteCarlo::setVariables(Graph *graph)
{
	this->node_id_map=graph->getNodeIdMap();
    this->adjTable=graph->getAdjTable();
    this->weakCoeff=graph->getWeakCoeff();
}

void MonteCarlo::init(std::vector<int> seed)
{
    seedvec=seed;
    for (int i=0; i<seed.size(); i++) {
        active_ids.insert(node_id_map[seed[i]]);
        active_nodes.insert(seed[i]);
    }
}


double MonteCarlo::simulation(int num_iter,std::vector<int> seed)
{
    //std::cout<<"starting simulation!"<<std::endl;
    int resultSize=0;
    
    for (int i=0; i<num_iter; i++)
    {
        seedvec.clear();
        active_nodes.clear();
        active_ids.clear();
        
        init(seed);
        resultSize+=active_nodes.size();
        
        int h=0;
        int t=seedvec.size();
        while (h<t)
        {
            std::vector<ADJ> adjs=adjTable[seedvec[h]];
            for (int i=0; i<adjs.size(); i++)
            {
                if (isActivated(seedvec[h],adjs[i].u,adjs[i].w))
                {
                	active_nodes.insert(adjs[i].u);
                    active_ids.insert(node_id_map[adjs[i].u]);
                    seedvec.push_back(adjs[i].u);
                    t++;
                    resultSize++;
                }
            }
            h++;
        }
    }
    double value=(double)resultSize/(double)num_iter;
    std::cout<<"spread value: "<<value<<std::endl;
    return (double)resultSize/(double)num_iter;
}

bool MonteCarlo::isActivated(int s,int t,double weight)
{
    if (active_nodes.count(t)) {
        return false;
    }else
    {
        int sid=node_id_map[s];
        int tid=node_id_map[t];
        double randval=(double)rand()/(double)RAND_MAX;
        if (active_ids.count(tid)) {
            if (tid==sid)
            {
                if (randval<weight)
                    return true;
            }else
            {
                if (randval<weight*weakCoeff[tid])
                    return true;
            }
        }else
        {
            if (randval<weight)
                return true;
        }
    }
    return false;
}

