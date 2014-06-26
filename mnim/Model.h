//
//  Model.h
//  mnim
//
//  Created by Anika on 6/20/14.
//
//
/**
 Model means hop_based influence calculation, 
 which calculate the influence between node pairs based on the hop propagation.
 **/

#ifndef __mnim__Model__
#define __mnim__Model__
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

class Model
{
private:
    int mode;
    
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
    
    //variables for maximum propagation path
    std::map<NODE,std::map<NODE,std::vector<ADJEDGE> > > mpp;
    std::map<NODE,std::map<NODE,double> > infval;
    
    std::map<NODE,std::vector<ADJEDGE> >tmpp;
    std::map<NODE,double> tmval;
    std::set<NODE> cans;
    NODE current_node;
    std::set<int> cain;
    
    // graph variables
    std::map<NODE, std::vector<ADJEDGE> > adjTable;
    std::set<int> nodes;
    std::map<int,double> naive;
    std::map<int, std::set<int> > nodenet;
    
    
public:
    Model(int mode);
    ~Model();
    void asynICM(int node);
    void synICM(int node);
    void SpreadICM(std::set<NODE> cnode);
    void traversal(int flag);
    void randominf();
    void pathRecord(NODE parent,NODE child,double w);
    void print(int flag);
    void MPPinf();
    void Dijkstra(NODE source);
    void printMpp();
    void spread();
    
    
    //return variables
    std::map<int,std::map<int,double> > getGlobalInf();
    std::map<int,std::map<NODE,infPath> > getGIP();
    
    //variables for asynchronous propagation process
    std::map<NODE,std::map<int,double> > getGlobalAsynInf();
    std::map<NODE,std::map<NODE,infPath> > getGIPAsyn();
    
    //variables for maximum propagation path
    std::map<NODE,std::map<NODE,std::vector<ADJEDGE> > > getMpp();
    std::map<NODE,std::map<NODE,double> > getMppInf();
};

#endif /* defined(__mnim__Model__) */
