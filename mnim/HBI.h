//
//  HBI.h
//  mnim
//
//  Created by Anika on 6/20/14.
//
//
/**
 HBI means hop_based influence calculation, 
 which calculate the influence between node pairs based on the hop propagation.
 **/

#ifndef __mnim__HBI__
#define __mnim__HBI__
#include <iostream>
#include <map>
#include "Graph.h"
#include "limit.h"
class HBI
{
private:
    //tmp variables
    //nodeStatus store the nodes status.
    std::map<NODE,int> nodeStatus;
    //CAN store the current active nodes;
    std::set<NODE> Can;
    //tmpinf store current influence value from source node to the current actived nodes along the active path
    std::map<NODE,double> tmpinf;
    
    // graph variables
    std::map<NODE, std::vector<ADJEDGE> > adjTable;
    std::set<int> nodes;
    std::map<int, std::set<int> > nodenet;
    
    
public:
    HBI();
    ~HBI();
    void asynCal(NODE node);
    void synCal(int node);
    void spread(std::set<NODE> cnode);
    void traversal();
    
};

#endif /* defined(__mnim__HBI__) */
