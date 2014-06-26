//
//  Seed.cpp
//  mnim
//
//  Created by Anika on 6/23/14.
//
//

#include "Seed.h"

Seed::Seed(){}

Seed::seed(int mode)
{
    this->mode=mode;
}

Seed::~Seed(){}

void Seed::topkSeed()
{
    
}

void Seed::heapData()
{
    if (mode==1) {
        
    }
    if (mode==2) {
        
    }
    if (mode==3) {
        std::map<NODE,std::map<NODE,double> >::iterator iter=infval.begin();
        while (iter!=infval.end()) {
            HeapNode hnode;
            double sumval=0.0;
            hnode.NODE=iter->first;
            std::map<NODE,double>::iterator iterinner=iter->second.begin();
            while (iterinner!=iter->second.end()) {
                sumval+=iterinner->second;
                iterinner++;
            }
            HeapData.push_back(hnode);
            iter++;
        }
    }
}

void Seed::setVariables()
{
    if (mode==1) {
        
    }
    if (mode==2) {
        
    }
    if(mode==3)
    {
        
    }
}