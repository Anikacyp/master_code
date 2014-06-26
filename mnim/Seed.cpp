//
//  Seed.cpp
//  mnim
//
//  Created by Anika on 6/23/14.
//
//

#include "Seed.h"

Seed::Seed(){
    
}

Seed::Seed(int mode)
{
    this->mode=mode;
    if(mode!=1 || mode!=2 || mode!=3)
        return;
    else
    {
        Model *model=new Model(mode);
        model->spread();
        setVariables(model);
        delete model;
    }
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
            hnode.node=iter->first;
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

void Seed::setVariables(Model * model)
{
    if (this->mode==1) {
        //variables for synchronous propagation process
        GlobalInf=model->getGlobalInf();
        GIP=model->getGIP();
    }
    if (this->mode==2) {
        //variables for asynchronous propagation process
       GlobalAsynInf=model->getGlobalAsynInf();
       GIPAsyn=model->getGIPAsyn();
    }
    if(this->mode==3)
    {
        //variables for maximum propagation path
        mpp=model->getMpp();
        infval=model->getMppInf();
    }
}