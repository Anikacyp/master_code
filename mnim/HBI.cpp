//
//  HBI.cpp
//  mnim
//
//  Created by Anika on 6/20/14.
//
//

#include "HBI.h"

HBI::HBI()
{
    Graph * graph=new Graph();
    graph->fileInput();
    graph->graphBuilding();
    this->nodes=graph->getNodes();
    this->adjTable=graph->getAdjTable();
    this->nodenet=graph->getNodeNet();
    delete graph;
}


HBI::~HBI(){}


void HBI::traversal()
{
    std::set<int>::iterator iter=nodes.begin();
    while (iter!=nodes.end()) {
        nodeStatus.clear();
        Can.clear();
        tmpinf.clear();
        
        synCal(*iter);
        
        iter++;
    }
}

void HBI::synCal(int node)
{
    std::map<NODE,double> tmpinf;
    std::set<int> tnet=nodenet[node];
    std::set<int>::iterator iter=tnet.begin();
    while (iter!=tnet.end()) {
        NODE tn;
        tn.node_id=node;
        tn.net_id=*iter1;
        Can.insert(tn);
        tmpinf[tn]=1;
        nodeStatus[tn]=1;
        iter++;
    }
    //initialize
    spread(Can);
    //std::cout<<std::endl;
}

void HBI::spread(std::set<NODE> node)
{
    std::set<NODE> tcan;
    std::set<NODE>::iterator iter=node.begin();
    while (iter!=node.end()) {
        std::vector<ADJEDGE> tadj=adjTable[*iter];
        for (int i=0; i<tadj.size(); i++) {
            if (!nodeStatus.count(tadj[i].dest)) {
                
            }
        }
        iter++;
    }
}


void HBI::asynCal(NODE node)
{
    
}
