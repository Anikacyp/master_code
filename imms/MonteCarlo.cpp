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
    //this->weakCoeff=graph->getWeakCoeff();
}

void MonteCarlo::init(std::vector<int> seed)
{
    active_nodes_tmp.clear();
    active_ids_tmp.clear();
    seedvec_tmp.clear();
    this->seedvec_tmp=seed;
    for (int i=0; i<seed.size(); i++) {
        this->active_ids_tmp.insert(node_id_map[seed[i]]);
        this->active_nodes_tmp.insert(seed[i]);
    }
}


double MonteCarlo::simulation(int num_iter,std::vector<int> seed)
{
    int resultSize=0;
    int uniq_num=0;
    init(seed);
    for (int i=0; i<num_iter; i++)
    {
        seedvec.clear();
        active_ids.clear();
        active_nodes.clear();
        seedvec=this->seedvec_tmp;
        active_ids=this->active_ids_tmp;
        active_nodes=this->active_nodes_tmp;
        
        //init(seed);
        //resultSize+=active_nodes.size();
        uniq_num+=active_ids.size();
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
                    //resultSize++;
                    if (!active_ids.count(node_id_map[adjs[i].u])) {
                        uniq_num++;
                        active_ids.insert(node_id_map[adjs[i].u]);
                    }
                }
            }
            h++;
        }
    }
    return (double)uniq_num/(double)num_iter;
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
        if (randval<weight) {
            
            return true;
        }
        /*int sid=node_id_map[s];
        int tid=node_id_map[t];
        double randval=(double)rand()/(double)RAND_MAX;
        if (active_ids.count(tid)) {
            if (tid==sid && randval<weight)
            {
                return true;
            }else
            {
                if(randval<(weight*weakCoeff[tid]))
                	return true;
            }
        }else
        {
            if (randval<weight)
            {
                active_ids.insert(tid);
                return true;
            }
        }*/
    }
    return false;
}

