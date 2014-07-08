//
//  MonteCarlo.cpp
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#include "MonteCarlo.h"
MonteCarlo::MonteCarlo(){}
MonteCarlo::~MonteCarlo(){}

void MonteCarlo::init(std::set<int> seed)
{
    std::set<int>::iterator iter_seed=seed.begin();
    while (iter_seed!=seed.end()) {
        seedvec.push_back(*iter_seed);
        active_nodes.insert(*iter_seed);
        active_ids.insert(node_id_map[*iter_seed]);
        iter_seed++;
    }
}


double MonteCarlo::simulation(int num_iter,std::set<int> seed)
{
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
                    seedvec.push_back(adjs[i].u);
                    t++;
                    resultSize++;
                }
            }
            h++;
        }
    }
    return (double)resultSize/(double)num_iter;
}

bool MonteCarlo::isActivated(int s,int t,double weight)
{
    if (active_nodes.count(id)) {
        return false;
    }else
    {
        int tid=node_id_map[t];
        int sid=node_id_map[s];
        double randval=(double)std::rand()/(double)std::RAND_MAX;
        if (active_ids.count(tid)) {
            if (tid==sid)
            {
                if (randval<weight) {
                    return true;
                }
            }else
            {
                if (randval<weight*weakCoeff[tid]) {
                    return true;
                }
            }
        }else
        {
            if (randval<weight) {
                return true;
            }
        }
    }
}