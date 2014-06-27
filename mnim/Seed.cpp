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

void Seed::setHeapData()
{
    if (mode==1) {
        std::map<int,std::map<int,double> >::iterator iter=GlobalInf.begin();
        while (iter!=GlobalInf.end()) {
            NODE tn(iter->first,0);
            HeapNode hnode;
            double sumval=0.0;
            hnode.node=tn;
            std::map<int,double>::iterator iterinner=iter->second.begin();
            while (iterinner!=iter->second.end()) {
                sumval+=iterinner->second;
                iterinner++;
            }
            heapData.push_back(hnode);
            iter++;
        }
    }
    if (mode==2) {
        std::map<NODE,std::map<int,double> >::iterator iter=GlobalAsynInf.begin();
        while (iter!=GlobalAsynInf.end()) {
            HeapNode hnode;
            double sumval=0.0;
            hnode.node=iter->first;
            std::map<int,double>::iterator iterinner=iter->second.begin();
            while (iterinner!=iter->second.end()) {
                sumval+=iterinner->second;
                iterinner++;
            }
            heapData.push_back(hnode);
            iter++;
        }
    }
    if (mode==3) {
        std::map<NODE,std::map<NODE,double> >::iterator iter=mppInf.begin();
        while (iter!=mppInf.end()) {
            HeapNode hnode;
            double sumval=0.0;
            hnode.node=iter->first;
            std::map<NODE,double>::iterator iterinner=iter->second.begin();
            while (iterinner!=iter->second.end()) {
                sumval+=iterinner->second;
                iterinner++;
            }
            heapData.push_back(hnode);
            iter++;
        }
    }
}

void Seed::setVariables(Model * model)
{
    //variables for synchronous propagation process
    if (this->mode==1) {
        GlobalInf=model->getGlobalInf();
        GIP=model->getGIP();
    }
    
    //variables for asynchronous propagation process
    if (this->mode==2) {
       GlobalAsynInf=model->getGlobalAsynInf();
       GIPAsyn=model->getGIPAsyn();
    }
    
    //variables for maximum propagation path
    if(this->mode==3)
    {
        mpp=model->getMpp();
        mppInf=model->getMppInf();
    }
}


void Seed::topkSeed()
{
    
}



