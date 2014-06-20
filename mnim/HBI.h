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
#include "Graph.h"
#include <iostream>
#include <map>

class HBI
{
private:
    std::map<NODE,int> NodeStatus;
    
public:
    HBI();
    ~HBI();
    void asyncleCal(NODE node);
    void syncCal(int node);
    
};

#endif /* defined(__mnim__HBI__) */
