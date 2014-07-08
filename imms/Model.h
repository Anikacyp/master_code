//
//  Model.h
//  imms
//
//  Created by Anika on 7/7/14.
//
//

#ifndef __imms__Model__
#define __imms__Model__

#include <iostream>
#include "Graph.h"
#include "Objects.h"
#include "limit.h"
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <stdlib.h>

class Model
{
private:
    //graph information & variables
    std::map<int,int> node_id_map;
    std::map<int,int> node_net_map;
    std::map<int,std::set<int> > node_set_map;
    std::map<int,double> weakCoeff;
    std::map<int,std::vector<ADJ> > adjTable;
    
    //tmp vairables
    std::set<int>tat;
    int current_node;
    std::map<int,double> tmppp;
    std::map<int,std::vector<ADJ> >tmppath;
    std::set<int> tmpS;
    std::set<int> tmpids;
    
    //result variables
    std::map<int,std::map<int,double> > miv;
    std::map<int,std::map<int,std::vector<ADJ> > >mip;
    
public:
    Model(Graph *graph);
    Model();
    ~Model();
    void traversal();
    void spread(int node);
    void recordPath(int source,int dest,double w);
    void MPP();
    void Dijkstra(int id);
    int randomNum(int range);
    void setVariables(Graph *graph);
    void print();
};

#endif /* defined(__imms__Model__) */
