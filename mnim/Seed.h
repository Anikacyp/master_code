//
//  Seed.h
//  mnim
//
//  Created by Anika on 6/23/14.
//
//

#ifndef __mnim__Seed__
#define __mnim__Seed__

#include <iostream>
#include "BaseObj.H"
#include "Heap.h"

class Seed
{
private:
    //variable for synchronous propagation process
    std::map<int,std::map<int,double> > GlobalInf;
    std::map<int,std::map<NODE,infPath> > GIP;
    
    
    //variables for asynchronous propagation process
    std::map<NODE,std::map<int,double> > GlobalAsynInf;
    std::map<NODE,std::map<NODE,infPath> > GIPAsyn;
    
    
    //variables for maximum propagation path
    std::map<NODE,std::map<NODE,std::vector<ADJEDGE> > > mpp;
    std::map<NODE,std::map<NODE,double> > infval;
    
    
    // graph variables
    std::map<NODE, std::vector<ADJEDGE> > adjTable;
    std::set<int> nodes;
    std::map<int,double> naive;
    std::map<int, std::set<int> > nodenet;
    
    
    //variables of the results
    std::map<int> seed_syn;
    std::map<NODE> seed_asyn;
    std::map<NODE> seed_mpp;
    
    
    //variables for the file
    std::vector<HeapNode> HeapData;
    /**
     note: mode means the propagation mode
     if(mode==1)
        synchronous propagation process
     if(mode==2)
        asynchronous propagation process
     if(mode==3)
        maximum propagation path pattern
     */
    int mode;
    
public:
    Seed(int mode);
    Seed();
    ~Seed();
    void topkSeed();
    void buildMIA();
    void buildMOA();
    void heapData();
    void setVariables();
};

#endif /* defined(__mnim__Seed__) */
