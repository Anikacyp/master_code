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
#include <cstdlib>
#include <ctime>
#include "Graph.h"
#include "limit.h"
struct infPath
{
    std::vector<ADJEDGE> path;
    double pp;
};

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
    std::map<int,double> tmpGinf;
    
    //tmp propagation path variable
    std::map<NODE, infPath> tmppath;
    
    //variable for synchronous propagation process
    std::map<int,std::map<int,double> > GlobalInf;
    std::map<int,std::map<NODE,infPath> > GIP;
    
    //variables for asynchronous propagation process
    std::map<NODE,std::map<int,double> > GlobalAsynInf;
    std::map<NODE,std::map<NODE,infPath> > GIPAsyn;
    
    
    // graph variables
    std::map<NODE, std::vector<ADJEDGE> > adjTable;
    std::set<int> nodes;
    std::map<int,double> naive;
    std::map<int, std::set<int> > nodenet;

public:
    HBI();
    ~HBI();
    void asynICM(int node);
    void synICM(int node);
    void spreadICM(std::set<NODE> cnode);
    void traversal(int flag);
    void randominf();
    void pathRecord(NODE parent,NODE child,double w);
    void print(int flag);
    
};

#endif /* defined(__mnim__HBI__) */
