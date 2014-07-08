//
//  MonteCarlo.h
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#ifndef __imms__MonteCarlo__
#define __imms__MonteCarlo__

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include "Objects.h"
#include "Graph.h"

class MonteCarlo
{
private:
    std::map<int,std::vector<ADJ> > adjTable;
    std::map<int,int> node_id_map;
    std::map<int,double> weakCoeff;
    
    //tmp variables
    std::set<int> active_nodes;
    std::set<int> active_ids;
    std::vector<int> seedvec;
public:
    MonteCarlo(Graph *graph);
    MonteCarlo();
    ~MonteCarlo();
    void init(std::vector<int> seed);
    double simulation(int num_iter, std::vector<int> seed);
    bool isActivated(int sid,int did,double weight);
    void setVariables(Graph *graph);
    //void setAdjTable(std::map<int,std::vector<ADJ> >adt);
    //void setNodeIdMap(std::map<int,int> nim);
    //void setWeakCoeff(std::map<int,double> wc);
    
};
#endif /* defined(__imms__MonteCarlo__) */
